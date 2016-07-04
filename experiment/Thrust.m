function [ thrust ] = Thrust( throttle, rocketPower, mass )
    %rocketPower = max thrust in kN
    thrust = (throttle * rocketPower * 1000) / mass;
end