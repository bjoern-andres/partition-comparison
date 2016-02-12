from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize


setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = [Extension("partition_comparison",
                             ["src/partition_comparison.pyx"],
                             include_dirs=["./include"],
                             language="c++")]
    )
