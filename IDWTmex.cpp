#include <mex.hpp>
#include <mexAdapter.hpp>
#include "wavelib-nonfftw-vs/wavelet2d.h"
#include <numeric>

using namespace matlab::data;
using matlab::mex::ArgumentList;
using matlab::engine::convertUTF8StringToUTF16String;

class MexFunction : public matlab::mex::Function {
public:
    void operator()(ArgumentList outputs, ArgumentList inputs) {
        
        ArrayFactory factory;
        
        // convert MATLAB containers to C++ containers
        const CellArray inSignalMatlabArray = inputs[0];
        int decompositionLevel = inSignalMatlabArray.getNumberOfElements();
        std::vector<int> length (decompositionLevel);
        std::vector<double> inSignal;
        for (int i = 0; i < decompositionLevel; ++i)
        {
            const TypedArray<double> tmp = inSignalMatlabArray[0][i];
            length[i] = tmp.getNumberOfElements();
            for (auto& is : tmp)
                inSignal.push_back (is);
        }
        length.push_back (std::accumulate (length.begin(), length.end(), 0));
        
        --decompositionLevel;
        
        const CharArray waveletTypeMatlabArray = inputs[1];
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
        std::vector<double> flag ({static_cast<double> ((length.back() % 2) == 0), 
                                   static_cast<double> (decompositionLevel)});
        
        // perform dwt
        idwt (inSignal, flag, waveletType, outSignal, length);
        
        // create output array
        outputs[0] = factory.createArray<double> ({1, outSignal.size()}, outSignal.data(), outSignal.data() + outSignal.size());
    }
};