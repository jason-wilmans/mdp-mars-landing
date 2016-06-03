function [ airDrag ] = AirDrag( speed, rocketDiameter )
    area = Area(rocketDiameter);
    
    airDrag = 0.5 * ResistenceCoefficient() * area * AirDensity() * speed * speed;
end

function [ area ] = Area( rocketDiameter )
    area = (3.14195 * rocketDiameter * rocketDiameter) / 4;
end

function [ cw ] = ResistenceCoefficient()
    %cw = 1.33;
    cw = 0.78;
end

function [ density ] = AirDensity()
    % density = 0.00903; % kg / m^3
    density = 1.29; % kg / m^3
end