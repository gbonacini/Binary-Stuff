#include <minIO.hpp>

int main(void){

   using minIO::strnlen,
         minIO::write,
         minIO::printScreen,
         minIO::open,
         minIO::close,
         minIO::uint64_t,
         minIO::O_CREAT,
         minIO::O_WRONLY,
         minIO::S_IRUSR,
         minIO::S_IWUSR,
         minIO::exit;

   int fd { open("/home/bg/_Sorgenti/_MinIO/examples/samplefile.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)  };
   if(fd < 0 ){
       printScreen("\nERR\n", 5);
       //exit(true);
   }

   const char* msg { "message\n" };
   write(fd, msg,  strnlen(msg, 9));
   close(fd);
   printScreen("\nEND\n", 5);
    
   exit();
}

