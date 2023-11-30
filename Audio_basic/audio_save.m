Fs = 44300;
noc1 = 1;
noc2 = 2;
nob = 16;
rob = audiorecorder(Fs, nob, noc1);

recordblocking(rob, 4);
myrecording = getaudiodata(rob, "double");
ch1 = myrecording(:, 1);
figure(1); plot(ch1);

sound(ch1, Fs);

filename = 'test_audio_file.wav';
audiowrite(filename,ch1,Fs)