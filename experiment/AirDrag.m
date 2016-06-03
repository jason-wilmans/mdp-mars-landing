function [ airDrag ] = AirDrag( speed, rocketDiameter, mass, height )    
    density = Density(height);
    
    area = Area(rocketDiameter);
    
    if speed >= 0
        cw = 0.34; % convex half sphere (approximation of rocket tip)
        airDrag = -1 * (0.5 * cw * area * density * speed * speed) / mass;
    else
        cw = 1.10; % concave half sphere (approximation of jet outlet)
        airDrag = (0.5 * cw * area * density * speed * speed) / mass;        
    end
end

function [ area ] = Area( rocketDiameter )
    area = (3.14195 * rocketDiameter * rocketDiameter) / 4;
end

function [ density ] = Density( height )
% result is gas density in kg * m^3
   
    % 15°C in K, (international standard atmosphere, https://de.wikipedia.org/wiki/Barometrische_Höhenformel)
    temperature = 288.15;
    
    %earth (https://de.wikipedia.org/wiki/Gaskonstante#Spezifische_Gaskonstante)
	gasConstant = 287.058;
   
   hPa = 1013.25 * (1 - (0.0065 * height) / 288.15).^5.255;
   density = hPa / (gasConstant * temperature);
   density = 1.293;
end