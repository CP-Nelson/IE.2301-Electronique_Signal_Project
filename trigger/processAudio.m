function [originalAudio, filteredAudio, Energy] = processAudio(audio_data, Fs)
    % Calculate the length of the audio data in seconds
    len_time = length(audio_data) / Fs;

    % Create a time series for plotting
    time = linspace(0, len_time, length(audio_data));

    % FFT Analysis
    nfft = 2^nextpow2(length(audio_data)); % Number of FFT points
    fft_result = fft(audio_data, nfft);
    fft_result = fft_result(1:nfft/2); % Keep only the first half
    frequencies = (0:nfft/2-1) * Fs / nfft; % Frequency axis

    % Designing Bandpass Filter
    center_freq = 300; % Center frequency of the bandpass filter
    normalized_center_freq = center_freq / (Fs/2); % Normalize center frequency
    bandpass_filter = fir1(10, [295, 305] / (Fs/2), 'bandpass'); % Bandpass filter

    % Applying the Bandpass Filter
    filtered_audio = filter(bandpass_filter, 1, audio_data);

    % FFT of the filtered signal
    filtered_fft_result = fft(filtered_audio, nfft);
    filtered_fft_result = filtered_fft_result(1:nfft/2); % First half
    amplitude_filtered = 20*log10(abs(filtered_fft_result)); % Amplitude in dB

    % Calculate the energy of the filtered audio signal
    Energy = eng(1, length(amplitude_filtered), amplitude_filtered);

    % Output structure for original and filtered audio
    originalAudio = struct('Time', time, 'Amplitude', audio_data);
    filteredAudio = struct('Time', time, 'Amplitude', filtered_audio);

    % Internal function for energy calculation
    function [energ] = eng(timeLeft, timeRight, amp)
        energ = 0;
        for i = timeLeft:timeRight
            if(amp(i) > 0)
                energ = energ + amp(i) * amp(i); % Energy calculation
            end
        end
    end
end

