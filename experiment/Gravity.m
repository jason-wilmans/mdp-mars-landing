function [ acceleration ] = Gravity( tankLevel, tankVolume )
% tankLevel is percent of tank left filled from 0.0 to 1.0
% tankVolume maximum volume in kg

    marsGravity = 3.711; % m/s*s

    acceleration = marsGravity * tankLevel * tankVolume;
end