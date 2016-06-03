function [ airDrag ] = AirDrag( speed, rocketDiameter, mass )
    % density = 0.00903; % kg / m^3
    density = 1.293; % kg / m^3
    
    %cw = 1.33;
    cw = 0.78;

    area = Area(rocketDiameter);
    
    airDrag = (0.5 * cw * area * density * speed * speed) / mass;
end

function [ area ] = Area( rocketDiameter )
    area = (3.14195 * rocketDiameter * rocketDiameter) / 4;
end