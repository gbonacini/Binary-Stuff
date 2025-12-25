#include <minIO.hpp>

int main(void){

   using minIO::printScreen,
         minIO::printNumber,
         minIO::strnlen,
         minIO::exit,
         minIO::uint64_t;

   const char* msg { "message\n" };
   volatile uint64_t ret{ printScreen(msg, strnlen(msg,9)) };

   printScreen("ret:", 4);
   printNumber(ret);
   printScreen("\n", 1);
   printNumber(1234567890);
   printScreen("\n", 1);
   exit();
}

