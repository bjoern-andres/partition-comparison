cimport cython

cdef extern from "andres/partition-comparison.hxx" namespace "andres":
   double variationOfInformation(...)

ctypedef fused Label:
    cython.char
    cython.uchar
    cython.short
    cython.ushort
    cython.long
    cython.ulong
    cython.longlong
    cython.ulonglong

def variation_of_information(Label[::1] x, Label[::1] y):
    assert x.size == y.size
    return variationOfInformation(&(x[0]), (&x[0]) + <int> x.size, &(y[0]), True)
