function outVector = IDWT(inValues, waveletType)
% IDWT computes the invcerse discrete Wavelet Transform of a cell array
% of wavelet subbands, as created by DWT. For proper reconstruction, please
% supply the same waveletType as you supplied to the DWT
% 
% Possible wavelet types are:
% db1, db2, db3, db4, db5, db6, db7, db8, db9, db10, db11, db12, db13, db14, db15
% bior1.1, bio1.3, bior1.5, bior2.2, bior2.4, bior2.6, bior2.8, bior3.1, bior3.3, 
% bior3.5, bior3.7, bior3.9, bior4.4, bior5.5, bior6.8
% coif1, coif2, coif3, coif4, coif5, haar

isThisACellArray(inValues)
isThisACharString(waveletType)

outVector = IDWTmex(inValues, waveletType);
end

