// g++ nml-position-logger.cc -I include -L lib -l nml -l linuxcnc -I /usr/include/linuxcnc
#include "emc.hh"
#include "emc_nml.hh"
#include "emcpos.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <tuple>

int i;

int main(int argc, char **argv) {
//    if(argc < 2) { std::cerr << "Usage: " << argv[0] << " NMLFILE\n"; abort(); }
//    const char *nmlfile = argv[1];
	const char *nmlfile = "/usr/share/linuxcnc/linuxcnc.nml";
    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", nmlfile);
    while(1) {
        usleep(100*1000);
        i++;
        if(!stat->valid()) continue;
        if(stat->peek() != EMC_STAT_TYPE) continue;
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());
        std::cout << "PollNr:= [" << " "
			<< i << "] "
			<< "Pos-X:= [" << " " << emcStatus->motion.traj.position.tran.x << "] "
            << "Pos-Y:= [" << " " << emcStatus->motion.traj.position.tran.y << "] "
            << "Pos-Z:= [" << " " << emcStatus->motion.traj.position.tran.z << "] " 
            <<"\n";
    }
    return 0;
}
