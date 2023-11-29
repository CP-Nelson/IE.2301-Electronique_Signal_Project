Fs = 44300;
noc1 = 1;
noc2 = 2;
nob = 16;
rob = audiorecorder(Fs, nob, noc1);

recordblocking(rob, 5);
myrecording = getaudiodata(rob, "double");

rob = audiorecorder(Fs, nob, noc2);

recordblocking(rob, 5);
myrecording = getaudiodata(rob, "double");


ch1 = myrecording(:, 1);
ch2 = myrecording(:, 2);

figure(1); plot(ch1);
figure(2); plot(ch2);

sound(ch1, Fs);
sound(ch2, Fs);