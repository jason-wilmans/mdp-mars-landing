% tankLevel is percent of tank left filled from 0.0 to 1.0
% tankVolume maximum volume in kg
function [ acceleration ] = Gravity( tankLevel, tankVolume )
    acceleration = marsGravity * tankLevel * tankVolume;
end