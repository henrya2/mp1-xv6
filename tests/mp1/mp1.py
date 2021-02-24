#! /bin/env python

import toolspath
from testing import Xv6Build, Xv6Test

class Getcount1(Xv6Test):
   name = "getcount1"
   description = "call getcount(SYS_exec)"
   tester = "ctests/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 10

class Getcount2(Xv6Test):
   name = "getcount2"
   description = "call getcount after opening/reading from a file"
   tester = "ctests/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 10

class Getcount3(Xv6Test):
   name = "getcount3"
   description = "call getcount in parent and child processes"
   tester = "ctests/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 10

import toolspath
from testing.runtests import main
main(Xv6Build, [Getcount1, Getcount2, Getcount3])
