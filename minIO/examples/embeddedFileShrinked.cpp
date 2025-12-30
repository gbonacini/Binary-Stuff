#include <libMinIO.hpp>

int main(void){

   using minIO::strnlen,
         minIO::write,
         minIO::read,
         minIO::printScreen,
         minIO::open,
         minIO::close,
         minIO::rename,
         minIO::uint64_t,
         minIO::O_CREAT,
         minIO::O_WRONLY,
         minIO::O_RDONLY,
         minIO::S_IRUSR,
         minIO::S_IWUSR,
         minIO::exit;

   int fd { open("./samplefile.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)  };
   if(fd < 0 ){
       printScreen("\nERR\n", 5);
       exit(true);
   }

   const char* msg { "message\n" };
   printScreen("\nWRT\n", 5);
   write(fd, msg,  strnlen(msg, 9));
   close(fd);
   printScreen("\nRD\n", 4);

   int rfd { open("./samplefile.txt", O_RDONLY)  };
   if(rfd < 0 ){
       printScreen("\nERR\n", 5);
       exit(true);
   }

   char rmsg[9] {};
   read(rfd, rmsg,  strnlen(msg, 9));
   printScreen(rmsg, strnlen(rmsg, 9)); 
   printScreen("\nREN\n", 5);
   int rtt { rename("./samplefile.txt", "./new_samplefile.txt") };
   if(rtt < 0 ){
       printScreen("\nERR\n", 5);
       exit(true);
   }
   printScreen("\nEND\n", 5);

   exit();
}

