function [Energy] = finalfilter(Fs,audio_data)

% Create time series to plot the data
nfft = 2^nextpow2(length(audio_data)); % Selecting the number of FFT points

lower_freq = 250;
upper_freq = 350;
filter_order = 19;

% Normalize frequencies
normalized_lower_freq = lower_freq / (Fs/2);
normalized_upper_freq = upper_freq / (Fs/2);

% Design a bandpass filter
bandpass_filter = fir1(filter_order, [normalized_lower_freq normalized_upper_freq], 'bandpass');

% Apply the bandpass filter to the audio data
filtered_audio = filter(bandpass_filter, 1, audio_data);

%% Filter apply %%
filtered_fft_result = fft(filtered_audio, nfft);
filtered_fft_result = filtered_fft_result(1:nfft/2);
amplitude_filtered = 20*log10(abs(filtered_fft_result));

% Calculate the energy of filtered audio signal
Energy = eng(1,length(amplitude_filtered),amplitude_filtered);

function [energ] = eng(timeLeft,timeRight,amp)
    energ = 0;
    for i = timeLeft:timeRight
        if(amp(i)>0)
        energ = energ + amp(i)*amp(i);
        end
    end
end
end
