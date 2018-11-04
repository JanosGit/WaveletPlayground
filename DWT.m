function outValues = DWT(inVector, decompositionLevel, method)
% DWT computes the discrete Wavelet Transform of a real-valued input vector
% with a desired decomposition level and the desired wavelet type.
% 
% Possible wavelet types are:
% db1, db2, db3, db4, db5, db6, db7, db8, db9, db10, db11, db12, db13, db14, db15
% bior1.1, bio1.3, bior1.5, bior2.2, bior2.4, bior2.6, bior2.8, bior3.1, bior3.3, 
% bior3.5, bior3.7, bior3.9, bior4.4, bior5.5, bior6.8
% coif1, coif2, coif3, coif4, coif5, haar


isThisARealValuedVector(inVector)
isThisANumericScalar(decompositionLevel)
isThisACharString(method)

% todo: checken ob method aus menge der gültigen methodennamen stammt

outValues = DWTmex(inVector, decompositionLevel, method);
end

