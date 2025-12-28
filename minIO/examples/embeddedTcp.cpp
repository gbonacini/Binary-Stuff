#include <minIO.hpp>

int main(void){

   using minIO::strnlen,
         minIO::write,
         minIO::read,
         minIO::printScreen,
         minIO::close,
         minIO::socket,
         minIO::connect,
         minIO::shutdown,
         minIO::Sockaddr,
         minIO::setIp,
         minIO::SOCK_TYPE,
         minIO::PROTOCOL_TYPE,
         minIO::FAMILY_TYPE,
         minIO::SHUTDOWN_TYPE,
         minIO::uint64_t,
         minIO::htons,
         minIO::shutdown,
         minIO::exit;

   int fd { socket(SOCK_TYPE::SOCK_STREAM, PROTOCOL_TYPE::IPPROTO_TCP)  };
   if(fd < 0 ){
       printScreen("\nSERR\n", 6);
       exit(true);
   }

   Sockaddr sockAddr {};
   setIp(sockAddr, 127,0,0,1);
   sockAddr.sin_port=htons(8088);
   sockAddr.sin_family = FAMILY_TYPE::AF_INET;

   int ret {connect(fd, &sockAddr, sizeof(sockAddr)) };
   if(ret < 0 ){
       printScreen("\nCERR\n", 6);
       exit(true);
   }
   const char* msg { "message\n" };
   printScreen("\nWRT\n", 5);
   ret = write(fd, msg,  strnlen(msg, 9));
   if(ret <  0 ){
       printScreen("\nWERR\n", 6);
   }

   char buff[5] {};
   printScreen("\nRED\n", 5);
   ret = read(fd, buff, 4);
   printScreen(buff, 4);

   shutdown(fd, SHUTDOWN_TYPE::SHUT_RDWR);
   close(fd);

   printScreen("\nEND\n", 5);

   exit();
}

