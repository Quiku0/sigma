
#!/usr/bin/python3
from distutils.core import setup
from distutils.core import Extension

Sigma=Extension("sigmaV1",["src/Sigma.c","src/algorithm_2.c","src/algorithm_3.c","src/matrix_0_1.c","src/partition_tree.c","src/files.c","src/graph.c"],
                    define_macros = [('MAJOR_VERSION', '1'),
                                    ('MINOR_VERSION', '0')],
                    include_dirs=['include','/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/numpy/core/include'])
setup(
    name='SiGma',
   version='1.0',
   description='',
   author='Maxence Buisson',
   author_email='',
   url='https://www.ibm.com',
    ext_modules=[Sigma]
    )