%% Transforms a mono audio signal into some wavelet subbands, plots the
%  originial signal and the subbands and then calculates the inverse
%  transform on the result.
clearvars
close all

%% Load some speech data
% !!!! For license reasons, no input Signal is included in the repo. Please
% supply a column vector of audio samples with the name inSignal and a
% corresponding sample rate with the name fSample to make this script work
inSignal =
fSample =
inSignalLengthInSecs = length(inSignal) * fSample;

%% Wavelet Transformation
decompositionLevel = 8;
waveletType = 'haar';
transformed = DWT(inSignal, decompositionLevel, waveletType);

%% Inverse Transformation
reconstructed = IDWT(transformed, waveletType);

%% Vizualisation
figure
subplot(2, 1, 1)
plot(inSignal)
title('Original signal')

subplot(2, 1, 2)
plot(reconstructed)
title('Reconstructed signal')

figure
subplot(length(transformed) + 1, 1, 1)
t = (1:length(inSignal)) ./ fSample;
plot(t, inSignal)
title('Originalsignal')
set(gca, 'XLim', [t(1), t(end)]);

fStart = 0;
bandwidth = fSample / 2;

for n = 1:length(transformed)
    subplot(length(transformed) + 1, 1, n + 1)
    t = linspace (1 / length(transformed{1, n}), inSignalLengthInSecs, length(transformed{1, n}));
    plot(t, transformed{1, n})
    set(gca, 'XLim', [t(1), t(end)]);
    
    if n == (length(transformed) + 1)
        bandwidth = bandwidth * 2;
    end
    
    title(['Subband ' num2str(n) ': ' num2str(fStart) 'Hz - ' num2str(fStart + bandwidth) 'Hz'])
    
    fStart = fStart + bandwidth;
    bandwidth = bandwidth / 2;
end