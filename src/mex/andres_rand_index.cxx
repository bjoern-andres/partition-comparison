#include "mex.h"

#include "partition-comparison.hxx"

template<class T>
double
matlabRandIndexHelper(
    const mxArray* array0,
    const mxArray* array1
)
{
    if(mxGetClassID(array0) != mxGetClassID(array1)) {
        mexErrMsgTxt("The two labelings do not have the same data type.\n");
    }

    if(mxGetNumberOfElements(array0) != mxGetNumberOfElements(array1)) {
        mexErrMsgTxt("The two labelings do not have the same size.\n");
    }

    const size_t n = mxGetNumberOfElements(array0);
    const T* p0 = static_cast<const T*>(mxGetData(array0));
    const T* p1 = static_cast<const T*>(mxGetData(array1));
    return andres::randIndex(p0, p0 + n, p1, true); // ignores default label 0
}

void mexFunction(
    int nlhs,
    mxArray *plhs[],
    int nrhs,
    const mxArray *prhs[]
)
{
    if(nrhs != 2) {
        mexErrMsgTxt("Incorrect number of parameters. Expecting two.\n");
    }
    if(nlhs > 1) {
        mexErrMsgTxt("Incorrect number of return parameters. Expecting one.\n");
    }

    double r;
    switch(mxGetClassID(prhs[0])) {
    case mxUINT8_CLASS:
        r = matlabRandIndexHelper<unsigned char>(prhs[0], prhs[1]);
        break;
    case mxINT8_CLASS: // char (not signed) according to MATLAB reference
        r = matlabRandIndexHelper<char>(prhs[0], prhs[1]);    
        break;
    case mxUINT16_CLASS:
        r = matlabRandIndexHelper<unsigned short>(prhs[0], prhs[1]);
        break;
    case mxINT16_CLASS: // short (not signed) according to MATLAB reference
        r = matlabRandIndexHelper<short>(prhs[0], prhs[1]);        
        break;
    case mxUINT32_CLASS:
        r = matlabRandIndexHelper<unsigned int>(prhs[0], prhs[1]);
        break;
    case mxINT32_CLASS: // int (not signed) according to MATLAB reference
        r = matlabRandIndexHelper<int>(prhs[0], prhs[1]);        
        break;
    case mxUINT64_CLASS:
        r = matlabRandIndexHelper<unsigned long long>(prhs[0], prhs[1]);
        break;
    case mxINT64_CLASS: // long long (not signed) according to MATLAB reference
        r = matlabRandIndexHelper<long long>(prhs[0], prhs[1]);        
        break;
    case mxSINGLE_CLASS:
        r = matlabRandIndexHelper<float>(prhs[0], prhs[1]);
        break;
    case mxDOUBLE_CLASS:
        r = matlabRandIndexHelper<double>(prhs[0], prhs[1]);
        break;
    default:
        mexErrMsgTxt("Data type not supported.\n");
        break;
    }

    plhs[0] = mxCreateDoubleScalar(r);
}
