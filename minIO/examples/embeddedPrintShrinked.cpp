#include <minIO.hpp>

int main(int argc, char** argv){

   using minIO::printScreen,
         minIO::printNumber,
         minIO::strnlen,
         minIO::exit;

   const char* msg { "message\n" };
   unsigned long long ret { printScreen(msg, 8) };
   printScreen("\nret:", 5);
   printNumber(ret);
   printScreen("\n", 1);
   
   exit();
}
