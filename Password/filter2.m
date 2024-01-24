function [Energy] = filter2(Fs,audio_data)
filtered_output = bandpassfilter(audio_data);
Energy = eng(1,length(filtered_output),filtered_output);
function [energ] = eng(timeLeft,timeRight,amp)
    energ = 0;
    for i = timeLeft:timeRight
        if(amp(i)>0)
        energ = energ + amp(i)*amp(i);
        end
    end
end

function [filtered_output]= bandpassfilter(Data)
Fs     = 1000;   
N      = 50;   % Order
Fstop1 = 200;  % First Stopband Frequency
Fpass1 = 250;  % First Passband Frequency
Fpass2 = 350;  % Second Passband Frequency
Fstop2 = 400;  % Second Stopband Frequency
Wstop1 = 0.001;    % First Stopband Weight
Wpass  = 0.057501127785;    % Passband Weight
Wstop2 = 0.0001;    % Second Stopband Weight
% Calculate the coefficients using the FIRLS function.
b  = firls(N, [0 Fstop1 Fpass1 Fpass2 Fstop2 Fs/2]/(Fs/2), [0 0 1 1 0 ...
       0], [Wstop1 Wpass Wstop2]);
filtered_output = filter(b,1,Data);
end
end