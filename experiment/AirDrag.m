function [ airDrag ] = AirDrag( speed, rocketDiameter, mass )
    % density = 0.00903; % kg / m^3
    density = 1.293; % kg / m^3
    
    area = Area(rocketDiameter);
    
    if speed >= 0
        cw = 1.15; % slightly better than a concave plate
        airDrag = -1 * (0.5 * cw * area * density * speed * speed) / mass;
    else
        cw = 1.15; % slightly better than a concave plate    
        airDrag = (0.5 * cw * area * density * speed * speed) / mass;        
    end
end

function [ area ] = Area( rocketDiameter )
    area = (3.14195 * rocketDiameter * rocketDiameter) / 4;
end