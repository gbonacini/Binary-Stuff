#include <minIO.hpp>

int main(void){

   using minIO::strnlen,
         minIO::printScreen,
         minIO::getChar,
         minIO::exit;

   const char* msg { "press 'return' to exit\n" };

   printScreen(msg, strnlen(msg, 24));
   while(true){
       char in { getChar() };
       if(in == '\n') break;
       printScreen(&in, 1);
   }
   printScreen("\nEND\n", 5);

   exit();
}

