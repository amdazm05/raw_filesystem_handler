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
         const char *dev_name;
         std::ifstream readfile;
         std::ofstream writefile;
    public:
         int drive_open(const char *drive_name);
         int drive_write(unsigned int sec, unsigned int num_secs, char *buf);
         int drive_read(unsigned int sec, unsigned int num_secs, char *buf);
         uint64_t get_drive_geometry();
};

#endif //__RD_LINUX
