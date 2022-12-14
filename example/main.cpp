#include <rdlinux.hpp>
#include <unistd.h>
int main(int argc, char * argv[])
{
    LinuxRWNFS diskWRHandler;
    diskWRHandler.drive_open("/dev/sdb1");
    std::cout<<diskWRHandler.get_drive_geometry()<<std::endl;
    char buffer[512]={};
    buffer[1]=0xFF;
    diskWRHandler.drive_write(1,1,buffer);
    // sleep(100);
    diskWRHandler.drive_read(1,1,buffer);
    for(int i=0;i<512;i++)
        printf("%x",*((uint8_t*)buffer+i));
    std::cout<<std::endl;
    return EXIT_SUCCESS;
}