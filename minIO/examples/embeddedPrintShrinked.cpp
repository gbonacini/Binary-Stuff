#include <minIO.hpp>

int main(void){

   using minIO::printScreen,
         minIO::printNumber,
         minIO::strnlen,
         minIO::write,
         minIO::numberToString,
         minIO::uint64_t,
         minIO::exit;

   const char* msg { "message\n" };
   volatile uint64_t ret { printScreen(msg, strnlen(msg,9)) };
   printScreen("\nret:", 5);
   printNumber(ret);
   volatile uint64_t anum { 0 };
   const char* converted { numberToString(anum) };
   printScreen("\nconv:", 6);
   printScreen(converted, strnlen(converted, 20));
   anum = 1234567890;
   converted = numberToString(anum);
   printScreen("\nconv:", 6);
   printScreen(converted, strnlen(converted, 20));
   write(1, "\nwrite",  6);
   printScreen("\nEND\n", 5);
    
   exit();
}

