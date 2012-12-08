cimport cython

from libc.stdint cimport int8_t, int16_t, int32_t, int64_t
from libc.stdint cimport uint8_t, uint16_t, uint32_t, uint64_t

cdef extern from "andres/partition-comparison.hxx" namespace "andres":
   double randIndex(...)
   double variationOfInformation(...)

ctypedef fused Label:
    int8_t
    int16_t
    int32_t
    int64_t
    uint8_t
    uint16_t
    uint32_t
    uint64_t

def rand_index(Label[::1] x, Label[::1] y):
    assert x.size == y.size
    return randIndex(&(x[0]), (&x[0]) + <int> x.size, &(y[0]), True)

def variation_of_information(Label[::1] x, Label[::1] y):
    assert x.size == y.size
    return variationOfInformation(&(x[0]), (&x[0]) + <int> x.size, &(y[0]), True)
