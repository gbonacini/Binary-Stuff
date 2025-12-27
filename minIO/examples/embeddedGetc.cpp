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
       switch(in){
         case 0:
              printScreen("\nERR\n", 5);
              exit();
         case '\n':
              printScreen("\nEND\n", 5);
              exit();
         default:
           printScreen(&in, 1);
       }
   }

}

