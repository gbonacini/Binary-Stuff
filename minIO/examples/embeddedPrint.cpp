#include <minIO.hpp>

int main(int argc, char** argv){

   using minIO::printScreen,
         minIO::strnlen;

   const char* msg { "message\n" };
   int ret         { printScreen(msg, strnlen(msg,9)) };
   
   return ret;
}
