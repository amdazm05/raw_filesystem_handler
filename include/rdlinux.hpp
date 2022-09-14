#ifndef __RD_LINUX
#define __RD_LINUX

//std includes
#include <cerrno>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>

class LinuxRWNFS
{
    private:
        static char *dev_name;
        static std::ifstream readfile;
        static std::ofstream writefile;
    public:
        static int drive_open(char *drive_name);    
        static int drive_write(unsigned int sec, unsigned int num_secs, char *buf);
        static int drive_read(unsigned int sec, unsigned int num_secs, char *buf);
        static uint64_t get_drive_geometry();
};

#endif //__RD_LINUX
