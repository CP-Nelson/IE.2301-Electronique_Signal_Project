function [energ] = energycalcul(timeLeft,timeRight,amp)
    energ = 0;
    for i = timeLeft:timeRight
        if(amp(i)>0)
        energ = energ + amp(i)*amp(i);
        end
    end
end