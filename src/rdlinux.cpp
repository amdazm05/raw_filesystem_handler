#include <rdlinux.hpp>


char *LinuxRWNFS::dev_name =NULL;
std::ifstream LinuxRWNFS::readfile;
std::ofstream LinuxRWNFS::writefile;

int LinuxRWNFS::drive_open(char *drive_name)

{
    //setting name once we open the drive
    dev_name=drive_name;
    readfile.open(drive_name, std::ios_base::binary);
    writefile.open(drive_name, std::ios_base::binary);
    if((!readfile)&&(!writefile))  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Unable to open drive : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }

    else
    {
        std::cout<<"LinuxRWNFS: Opened drive for operations"<<std::endl;
        return 0;
    }

}

uint64_t LinuxRWNFS::get_drive_geometry()
{
    readfile.close();
    readfile.open(dev_name, std::ios_base::binary | std::ios_base::ate);
    if(!readfile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Unable to open drive : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }
    uint64_t sizeofPartition= readfile.tellg();
    return sizeofPartition;
}

int LinuxRWNFS::drive_read(unsigned int sec, unsigned int num_secs, char *buf)
{
    readfile.close();
    //It is important to open the drive again to see whether the file is updated or not !
    readfile.open(dev_name,std::ios_base::binary);
    if(!readfile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Unable to open drive : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }

    readfile.seekg(512*sec);

    if(!readfile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Unable to seek the sector startoffset : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }

    readfile.read(buf,512*num_secs);
    if(!readfile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Couldn't read the sectors mentioned : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }

    //if all goes well
    return 0;
}


int LinuxRWNFS::drive_write(unsigned int sec, unsigned int num_secs, char *buf)
{
    //Close the drive to makesure its not opened in the ifstream
    // readfile.close();
    writefile.close();
    writefile.open(dev_name,std::ios_base::binary);
    if(!writefile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Unable to open drive : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }
    writefile.seekp(512*sec);

    if(!writefile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Unable to seek the sector startoffset : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }

    writefile.write(buf,512*num_secs);
    if(!writefile)  //NULL-condition incase nothing was opened.
    {
        std::cerr<<"LinuxRWNFS: Couldn't write the sectors mentioned : Error ! "<<std::strerror(errno)<<std::endl;
        return -1;
    }

    //if all goes well
    return 0;
}

