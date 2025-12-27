#include <minIO.hpp>

int main(void){

   using minIO::strnlen,
         minIO::write,
         minIO::printScreen,
         minIO::open,
         minIO::close,
         minIO::unlink,
         minIO::getChar,
         minIO::uint64_t,
         minIO::O_CREAT,
         minIO::O_WRONLY,
         minIO::O_RDONLY,
         minIO::S_IRUSR,
         minIO::S_IWUSR,
         minIO::exit;

   int fd { open("./to_delete.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)  };
   if(fd < 0 ){
       printScreen("\nERR\n", 5);
       exit(true);
   }

   const char* msg { "message\n" };
   printScreen("\nWRT\n", 5);
   write(fd, msg,  strnlen(msg, 9));
   close(fd);
   const char* gmsg { "press 'return' to delete the file and exit\n" };
   printScreen(gmsg, strnlen(gmsg, 44));
   while(true)
      if(getChar() == '\n') break;

   int rtt { unlink("./to_delete.txt") };
   if(rtt < 0 ){
       printScreen("\nERR\n", 5);
       exit(true);
   }
   printScreen("\nEND\n", 5);

   exit();
}

