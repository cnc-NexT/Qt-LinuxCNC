#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QBuffer>
#include <QtCore/QDebug>
#include <QTime>
#include <QThread>
#include <QTextStream>
#include <QMessageBox>
#include <QLCDNumber>
#include <QProcess>
#include <QString>
#include <QWidgetList>
#include <QTreeWidget>
#include <QLabel>
#include <QFrame>

#include <QTextBrowser>
#include <qstring.h>
#include <stdlib.h>
#include <tuple>

#include "emc.hh"
#include "emc_nml.hh"
#include "emcpos.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>


//#include "/home/udos/LLExec_PluginHeaders/LLSymbols/LLSymbols.h"


#define ARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define _tprintf printf


//-- VARS START ----------------------------------------------------------------------------------------
int	tagvalue =	0;
int cycles;
int cntValue;
int plc_dint_00;
int plc_udint_00;

QString txtwrite;
QString txtresult;
QString txt_plc_dint_00;
QString txt_plc_udint_00;

QString txt_countUp;
QString txt_countDown;


//-- TestBasic --
/*    LLSymWorkspaceHandle wks = 0;
    LLSymWorkspaceHandle wksHandle = 0;
    LLSymTagHandle      tag = 0;
    LLSymResult         result ;
    LLSymTagHandle      tagArr = 0;
    LLSymTagHandle      tagStr = 0;
    LLSymTagHandle**    out_tagList;
    LLSymTagHandle*     tagList;
    LLSymTagHandle      tagHandle;
    LLSymTypeHandle     dtypeStr = 0;
    LLSymTypeHandle     typeHandle;
    TCHAR               name[100];
    TCHAR               descr[100];
    TCHAR               type[20];
    llsym_addr_t        address;
    bool_t              bitvalue = 0;
    bool_t              done;
    bool_t              readonly;
    bool_t              isBitAddress;
    float32_t           fTagValue;
*/
    uint32_t            dim[3];
    short               value = 0;
    uint32_t            dataSize = 0;
    uint16_t            bufsize;
    uint32_t            out_numTags;
    uint32_t            numTags;

    int                 RCS_STAT_CHANNEL_STATE = 0;

    RCS_STAT_CHANNEL    *stat;

#ifdef _LLSYMBOLS_HAS_VARIANT
        VARIANT         varValue;
        VariantInit(&varValue);
#endif
//-- VARS END ----------------------------------------------------------------------------------------


//== ===== TIMER ================================================================
void MainWindow::updateRandomNumber()
    {
        QString rand_val = QString::number(qrand());
        ui->textEdit->setText("RANDOM Nr:= "    +   rand_val);
    }
//== ===== END TIMER ============================================================

//** START treeViewWidget ***********************************************************
void MainWindow::addTreeRoot(QString tagNumber, QString tagName, QString tagType)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem(ui->tw_LLX_Symbols);
        itm->setText(0, tagNumber);
        itm->setText(1, tagName);
        itm->setText(2, tagType);
    }
/*
void MainWindow::addTreeChild(QTreeWidgetItem *parent, QString name, QString Description, QString tagType )
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();
        itm->setText(0,name);
        itm->setText(1,Description);
        parent->addChild(itm);
    }
*/
//** END treeViewWidget ***********************************************************


//** Main::Window APP START ***********************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//  showMaximized();
    showFullScreen();

    //** Read STYLES SHEET ****************************************************************************
        QFile stylefile(":/LLSymStyles.qss");
        stylefile.open(QFile::ReadOnly | QFile::Text);
        QString styleSheet = stylefile.readAll();
        stylefile.close();
        qApp->setStyleSheet(styleSheet);

//== UPDATE TIMER START =======================================================
    cycles  =   0;
    connect(&timer, SIGNAL(timeout()), this, SLOT (updateRandomNumber()));
    timer.start(50);
    if (timer.isActive())
     {
        connect(&timer,SIGNAL(timeout()), this, SLOT(updnmlval()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(updateRandomNumber()));
     }
//== UPDATE TIMER END ========================================================

/*
// ** LLSymbols INIT ******************************************************************************
   const LLSymServerAddress GDBConn =
           { symProtGDB_TCP,
             {
                 _T("127.0.0.1"), 5000, 0
             }
           };

// LLSymAssert(result = LLSym_Init());
   result = LLSym_Init();
   txtwrite.append ("-- 1.) ************* LLSym_Init result:= "   +   QString::number(result)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");

//   LLSymAssert(result = LLSym_OpenWorkspace(0, &GDBConn, &wks));
   result = LLSym_OpenWorkspace(0, &GDBConn, &wks);
   txtwrite.append ("-- 2.) ************* LLSym_OpenWorkspace result:= "   +   QString::number(result)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");

   TCHAR symTabCopy[MAX_PATH] = ( _T("/data/plc/PLCcopy.sym.xml"));
   result = LLSym_GetSymbolTable(wks, symTabCopy, TRUE);
   txtwrite.append ("-- 3.) ************* LLSym_GetSymbolTable result:= "   +   QString::number(result)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");

   result  =   LLSym_GetGlobalTagsNum(wks, &out_numTags);
   txtwrite.append ("-- 4.) ************* LLSym_GetGlobalTagsNum result:= "   +   QString::number(result)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");
   txtwrite.append ("-- 5.) ************* LLSym_GetGlobalTagsNum out_numTags:= "   +   QString::number(out_numTags)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");

   result  =   LLSym_GetGlobalTags(wks, &tagList,  &out_numTags);
   txtwrite.append ("-- 6.) ************* LLSym_GetGlobalTags result:= "   +   QString::number(result)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");
   txtwrite.append ("-- 7.) ************* LLSym_GetGlobalTags &out_numTags:= "   +   QString::number(out_numTags)    +   "\n");
   ui->tb_StartUpInfo->setText(txtwrite   +   "\n");


// ** SetUp treeWidget ****************************************************************************
   ui->tw_LLX_Symbols->setColumnCount(3);
   ui->tw_LLX_Symbols->header()->setMinimumSectionSize(60);
   ui->tw_LLX_Symbols->header()->resizeSection(0,60);
   ui->tw_LLX_Symbols->header()->resizeSection(1,280);

    result = LLSym_GetGlobalTags(wks, &tagList,  &numTags);         //Get how many tags
    for (uint32_t i = 0;    i < numTags;   i++)
    {
        bufsize = ARRSIZE(name);
        result = LLSym_GetTagName(tagList[i], name, &bufsize);      //tag[i] name
        result = LLSym_GetTagDataType(tagList[i], type, &bufsize);  //tag[i] type
        QString n = QString::number(i);
        QString r = name;
        QString t = type;
        n = n.right(4);
        r = r.leftJustified(280, ' ');
        t = t.leftJustified(20, ' ');
// ** Write tagNames and tagTypes into treeWidget *************************************************
        addTreeRoot(n,r,t);
// ** Write tagNames and tagTypes into textBrowser ************************************************
        txtwrite.append("-- plctag [ "
                        + QString::number(i)
                        + " ] tagName:= "
                        + name
                        + "   tagType:= "
                        + type
                        + "\n");
        ui->tb_StartUpInfo->setText(txtwrite + "\n");
   }
    result  =   LLSym_FreeTagList(tagList);  //Release the tagList
// ** LLSymbols END ********************************************************************************
*/
//** CREATE RCS_STAT_CHANNEL *stat ****************************************************************
    const char *nmlfile = "/opt/linuxcnc/configs/common/linuxcnc.nml";
    stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", nmlfile);
    txtwrite.append ("-- 8.) ************* RCS_STAT_CHANNEL *stat CREATED  \n");
    ui->tb_StartUpInfo->setText(txtwrite   +   "\n");
}
//** Main::Window APP END *************************************************************************

MainWindow::~MainWindow()
{
    delete ui;
}

//** START NML Comunication ***********************************************************************
//void MainWindow::on_pbtn_00_MenuLeft_pressed()
//     txtwrite.append ("-- 9.) *************  XAxisPos  \n");
//     ui->textBrowser->setText(txtwrite   +   "\n");

void MainWindow::updnmlval()
    {
      if(!stat->valid())
      txtwrite.append ("-- 9.) ************* *stat:= INVALID \n");
      ui->tb_StartUpInfo->setText(txtwrite   +   "\n");

      if(stat->valid())
      {
       if(stat->peek() == EMC_STAT_TYPE)
       {
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

//Returns double obj containing the CMD pos in ABS coords,
        double xAxisPosAbsCMD = emcStatus->motion.traj.position.tran.x;
        double yAxisPosAbsCMD = emcStatus->motion.traj.position.tran.y;
        double zAxisPosAbsCMD = emcStatus->motion.traj.position.tran.z;

//Returns double obj containing the CMD pos in REL coords,
        double xAxisPosRelCMD = (emcStatus->motion.traj.position.tran.x -
                               emcStatus->task.g5x_offset.tran.x -
                               emcStatus->task.g92_offset.tran.x -
                               emcStatus->task.toolOffset.tran.x);

//Returns double objs containing the ACT pos in REL coords,
        double xAxisPosRelACT = (emcStatus->motion.traj.actualPosition.tran.x -
                                       emcStatus->task.g5x_offset.tran.x -
                                       emcStatus->task.g92_offset.tran.x -
                                       emcStatus->task.toolOffset.tran.x);

        double yAxisPosRelACT = (emcStatus->motion.traj.actualPosition.tran.y -
                                       emcStatus->task.g5x_offset.tran.y -
                                       emcStatus->task.g92_offset.tran.y -
                                       emcStatus->task.toolOffset.tran.y);

        double zAxisPosRelACT = (emcStatus->motion.traj.actualPosition.tran.z -
                               emcStatus->task.g5x_offset.tran.z -
                               emcStatus->task.g92_offset.tran.z -
                               emcStatus->task.toolOffset.tran.z);

//Returns double objs containing the ACT pos in ABS coords,
        double xAxisPosAbsACT = emcStatus->motion.traj.actualPosition.tran.x;
        double yAxisPosAbsACT = emcStatus->motion.traj.actualPosition.tran.y;
        double zAxisPosAbsACT = emcStatus->motion.traj.actualPosition.tran.z;

//Returns double obj containing Total distance_to_go,
        double allAxisDTG = emcStatus->motion.traj.distance_to_go;

//Returns double obj containing dtg x|y|..... ,
        double  xAxisDTG  = emcStatus->motion.traj.dtg.tran.x;
        double  yAxisDTG  = emcStatus->motion.traj.dtg.tran.y;
        double  zAxisDTG  = emcStatus->motion.traj.dtg.tran.z;

        double aAxisDTG = emcStatus->motion.traj.dtg.a;
        double bAxisDTG = emcStatus->motion.traj.dtg.b;
        double cAxisDTG = emcStatus->motion.traj.dtg.c;



        ui->lbl_X_AxisPosAct->setText( QString::number(xAxisPosAbsACT, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Y_AxisPosAct->setText( QString().setNum(yAxisPosAbsACT, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Z_AxisPosAct->setText( QString().setNum(zAxisPosAbsACT, 'f', 4) ); //setNum(num, 'g', 3) );

        ui->lbl_X_AxisPosCMD->setText( QString::number(xAxisPosAbsCMD, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Y_AxisPosCMD->setText( QString::number(yAxisPosAbsCMD, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Z_AxisPosCMD->setText( QString::number(zAxisPosAbsCMD, 'f', 4) ); //setNum(num, 'g', 3) );

        ui->lbl_AllAxisDTG->setText( QString().setNum(allAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_X_AxisDTG->setText( QString().setNum(xAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Y_AxisDTG->setText( QString().setNum(yAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Z_AxisDTG->setText( QString().setNum(zAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );

       }
      }
    }

//** BUTTON Functions *****************************************************************************
void MainWindow::on_pbtn_00_MenuBottom_pressed()
    {

    }

void MainWindow::on_pbtn_00_MenuBottom_released()
    {

    }

void MainWindow::on_pbtn_09_MenuBottom_pressed()
{
    close();
}



