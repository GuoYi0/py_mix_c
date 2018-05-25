import sys
import os
sys.path.append(os.getcwd() + "/build/lib.win-amd64-3.6/")
import Extest
import time
from ctypes import *
import os
# extest = cdll.LoadLibrary("E:\py_mix_c2\\build\\temp.win-amd64-3.6\Release\Extest.cp36-win_amd64.lib")
start = time.time()
a = Extest.reverse("abcd")
timeC = time.time() - start
print ('C costs', timeC, 'the result is', a)

start = time.time()
b = list("abcd")
b.reverse()
b = ''.join(b)
timePython = time.time()-start
print ('Python costs', timePython, 'the result is', b)