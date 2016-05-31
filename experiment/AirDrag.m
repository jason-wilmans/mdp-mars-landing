function [ airDrag ] = AirDrag( speed, rocketDiameter )
    airDrag = 0.5 * ResistenceCoefficient() * Area(rocketDiameter) * AirDensity() * speed * speed;
end

function [ area ] = Area( rocketDiameter )
    area = (3.14195 * rocketDiameter * rocketDiameter) / 4;
end

function [ cw ] = ResistenceCoefficient()
    cw = 1.33;
end

function [ density ] = AirDensity()
    density = 1.33;
end