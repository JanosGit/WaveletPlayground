% Compiles all mex files used for the WaveletPlayground
mex DWTmex.cpp wavelib-nonfftw-vs/kiss_fft.c wavelib-nonfftw-vs/wavelet2d.cpp
mex IDWTmex.cpp wavelib-nonfftw-vs/kiss_fft.c wavelib-nonfftw-vs/wavelet2d.cpp