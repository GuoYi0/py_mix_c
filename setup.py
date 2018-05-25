"""
编译的主要内容在setup.py里面，需要为每一个拓展创建一个Extension实例
Extension('Extest', sources=['Extest.c'])，第一个参数是扩展的名字，如果模块是包的一部分，还需要加"."；
第二个参数是源代码文件列表
setup('Extest', ext_modules=[...])，第一个参数表示要编译哪个东西，第二个参数列出要编译的Extension对象。
"""

from distutils.core import setup, Extension
MOD = 'Extest'
setup(name=MOD, ext_modules=[Extension(MOD, sources=['Extest.c'])])