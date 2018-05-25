运行环境，win10 + pycharm Python 3.6.4
步骤如下：
1、写Extest.c和setup.py两个模块。其中Extest.c用C语言定义了C函数，以及相应的包装函数，setup.py定义了编译文件。
2、编译。在命令行运行python setup.py build，就会生成一个build文件夹，在里面的子文件夹lib.win-amd64-3.6里面有个.pyd文件
   相当于动态链接库了。
3、使用函数。创建一个test.py模块，在里面import Extest以后，即可调用里面的函数了

注意，如果在编译的时候，使用的语句是
python setup.py build
那么直接import Extest会报错，需要将.pyd文件所在的地址添加进去，
即把sys.path.append(os.getcwd() + "/build/lib.win-amd64-3.6/")放在import Extest之前

也可以在编译的时候，使用语句
python setup.py build_ext --inplace
那么生成的Extest.cp36-win_amd64.pyd就直接在当前目录，直接import Extest就行