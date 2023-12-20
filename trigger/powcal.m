function [pow] = powcal(timeLeft,timeRight,amp)
    pow=0;
    for i = timeLeft:timeRight
        pow = pow + amp(i)^2;
    end
end