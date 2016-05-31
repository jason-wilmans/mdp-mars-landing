function [ acceleration ] = Acceleration( thrust, tankLevel, tankVolume, speed, rocketDiameter )
    acceleration = Thrust(thrust) - Gravity(tankLevel, tankVolume) + AirDrag(speed, rocketDiameter);
end