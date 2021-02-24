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

  assert(getcount(SYS_fork) == 0);
  printf(1, "abracadabra\n");
  if (fork() == 0) {
	assert(getcount(SYS_fork) == 0);
	printf(1, "hocuspocus\n");
    assert(getcount(SYS_write) == 11);
	exit();
  } else {
    wait();
	assert(getcount(SYS_fork) == 1);
	printf(1, "shazam!\n");
	assert(getcount(SYS_write) == 20); 
  }
  assert(getcount(SYS_wait) == 1);
  printf(1, "PASSED TEST!\n");
  exit();
}
