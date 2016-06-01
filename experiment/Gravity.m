function [ acceleration ] = Gravity( bruttoWeight, tankLevel, tankVolume )
% tankLevel is percent of tank left filled from 0.0 to 1.0
% tankVolume maximum volume in t

     earthGravity = 9.81; % m/s*s
%    marsGravity = 3.711; % m/s*s
    tonnesToNewton = 9.8 * 1000; % 9.8 N/kg * 1000 kg/t

    acceleration = earthGravity * tonnesToNewton * (bruttoWeight + tankLevel * tankVolume);
end