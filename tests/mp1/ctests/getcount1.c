#include "types.h"
#include "user.h"
#include "syscall.h"

#define assert(x) if (x) { /* pass */ } else { \
   printf(1, "assert failed %s %s %d\n", #x , __FILE__, __LINE__); \
   printf(1, "TEST FAILED\n"); \
   exit(); \
   }

int
main(int argc, char *argv[])
{
  assert(getcount(SYS_exec) == 1);
  printf(1, "PASSED TEST!\n");
  exit();
}
