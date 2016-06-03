function [ thrust ] = Thrust( throttle, rocketPower )
    %rocketPower max thrust in kN
    thrust = throttle * rocketPower;
end