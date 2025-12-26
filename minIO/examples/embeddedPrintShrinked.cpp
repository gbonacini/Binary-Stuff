#include <minIO.hpp>

int main(void){

   using minIO::printScreen,
         minIO::printNumber,
         minIO::strnlen,
         minIO::uint64_t,
         minIO::exit;

   const char* msg { "message\n" };
   volatile uint64_t ret { printScreen(msg, strnlen(msg,9)) };
   printScreen("\nret:", 5);
   printNumber(ret);
   printScreen("\nEND\n", 5);
   
   exit();
}

