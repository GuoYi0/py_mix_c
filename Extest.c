/*python 和C混合编程案例*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 引入Python.h头文件
#include "Python.h"

#define BUFSIZE 10

//定义一个阶乘函数
int fac(int n) {
    if (n < 2)
        return 1;
    return n * fac(n - 1);
}

//字符串翻转函数
char *reverse(char *s) {
    register char t;
    char *p = s;
    char *q = (s + (strlen(s) - 1));
    while (p < q) {
        t = *p;
       *p++ = *q;
       *q-- = t;
    }
    return s;
}

/*必须为每个模块都增加一个形如
static PyObject * Module_func()的包装函数。
包装函数的作用就是先把Python变量转换为c变量，再计算，然后将返回值转换为Python变量
必须是静态函数，返回值是PyObject *类型，包装函数的函数名必须是 "模块名_被包装函数名"形式

*/
static PyObject *
Extest_fac(PyObject *self, PyObject *args) {
    int res;  //计算结果
    int num;  //参数
    PyObject* retval;  //返回值

    // 将python参数解析为C参数，i表示解析为整型，赋给num
    res = PyArg_ParseTuple(args, "i", &num);
    if (!res) {  //解析失败，
        return NULL;
    }
    res = fac(num); //计算

    //把c计算的结果转换为python变量，即python对象
    retval = (PyObject *)Py_BuildValue("i", res);
    return retval;
}

static PyObject *
Extest_reverse(PyObject *self, PyObject *args) {
    char *orignal;
    if (!(PyArg_ParseTuple(args, "s", &orignal))) {
        return NULL;
    }
    return (PyObject *)Py_BuildValue("s", reverse(orignal));
}

static PyObject *
Extest_doppel(PyObject *self, PyObject *args) {
    char *orignal;
    char *resv;
    PyObject *retval;
    if (!(PyArg_ParseTuple(args, "s", &orignal))) {
        return NULL;
    }
    /*这里，我们既想返回原来的字符串，也想返回翻转以后的字符串，即返回两个值，
    _strdun()用于复制一份字符串，保存在resv开辟的内存空间中
    "ss"表示两个字符串
    */
    retval = (PyObject *)Py_BuildValue("ss", orignal, resv=reverse(_strdup(orignal)));
    free(resv); //释放内存空间
    return retval;
}

/*为每个模块都要增加一个形如PyMethodDef ModuleMethods[]的数组，官方名叫 method table
我们已经创建了几个包装函数，需要在这里把他们以数组形式列出来，以便python解释器能够导入他们，
各式如下
数组的每个元素中，第一个是字符串，原函数名；第二个是包装函数名，第三个一般为METH_VARARGS 或者 METH_VARARGS | METH_KEYWORDS
其中METH_VARARGS表示该函数以元组形式解析参数
第四个为该函数的doc
*/
static PyMethodDef
ExtestMethods[] = {
    {"fac", Extest_fac, METH_VARARGS, "function 1"},
    {"doppel", Extest_doppel, METH_VARARGS, "function 2"},
    {"reverse", Extest_reverse, METH_VARARGS, "function 3"},
    {NULL, NULL, 0, NULL},  //代表声明结束
};


/*模块定义结构体*/
static struct PyModuleDef Extest = {
    PyModuleDef_HEAD_INIT,
    "Extest", //模块名
    "This is a extest_doc", //模块的介绍文档
    -1,
    ExtestMethods  //上面定义的method table
};

/*最终，定义一个初始化函数，这也是唯一一个非静态函数，用于初始化
函数名必须命名为PyInit_name()，其中name是模块名
*/
PyMODINIT_FUNC PyInit_Extest(void){
    return PyModule_Create(&Extest);
}