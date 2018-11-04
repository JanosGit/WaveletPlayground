#include <mex.hpp>
#include <mexAdapter.hpp>
#include "wavelib-nonfftw-vs/wavelet2d.h"

using namespace matlab::data;
using matlab::mex::ArgumentList;
using matlab::engine::convertUTF8StringToUTF16String;

class MexFunction : public matlab::mex::Function {
public:
    void operator()(ArgumentList outputs, ArgumentList inputs) {
        
        ArrayFactory factory;
        
        // convert MATLAB containers to C++ containers
        const TypedArray<double> inSignalMatlabArray = inputs[0];
        std::vector<double> inSignal;
        for (auto iv : inSignalMatlabArray)      
            inSignal.push_back (iv);
        int decompositionLevel = inputs[1][0];
        const CharArray waveletTypeMatlabArray = inputs[2];
        std::string waveletType = waveletTypeMatlabArray.toAscii();

        // check if waveletType is correct
        std::vector<double> lp1, hp1, lp2, hp2;
        if (filtcoef (waveletType, lp1, hp1, lp2, hp2) == -1)
        {
            std::cerr << waveletType << " is an unknown identifier" << std::endl;
            outputs[0] = factory.createEmptyArray();
            return;
        }            
        // output vectors
        std::vector<double> outSignal (inSignal.size());
        std::vector<double> flag (2);
        std::vector<int> length;
        
        // perform dwt
        dwt (inSignal, decompositionLevel, waveletType, outSignal, flag, length);
        
        // create output cell array
        unsigned long numOutSignals = length.size() - 1;
        CellArray outSignals = factory.createCellArray({ 1, numOutSignals });
        unsigned long outOffset = 0;
        for (int i = 0; i < numOutSignals; ++i)
        {
            unsigned long len = length[i];
            double* start = outSignal.data() + outOffset;
            double* end   = start + len - 1;
            outOffset += len;

            outSignals[0][i] = factory.createArray<double> ({1, len}, start, end);
        }
    
        outputs[0] = outSignals;
    }
};