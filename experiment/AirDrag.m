function [ airDrag, density ] = AirDrag( speed, rocketDiameter, mass, height )    
    density = Density(height);
    
    area = Area(rocketDiameter);
    
    if speed >= 0
        cw = 0.1; % better than convex half sphere (approximation of rocket tip)
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
   
    % earth    
    % (https://de.wikipedia.org/wiki/Gaskonstante#Spezifische_Gaskonstante)
	% gasConstant = 287.058;
    % 15°C in K, (international standard atmosphere, https://de.wikipedia.org/wiki/Barometrische_Höhenformel)
    % temperature = 288.15;
    % groundPressure = 1013.3;
    % temperatureGradient = 0.0065;    
    
    % mars https://de.wikipedia.org/wiki/Mars_(Planet)
    temperature = 218.0;
    %(https://de.wikipedia.org/wiki/Gaskonstante#Spezifische_Gaskonstante + calculation)
    gasConstant = 191.5204402;
    % https://de.wikipedia.org/wiki/Mars_(Planet)
    groundPressure = 6.36;
    temperatureGradient = 0.0043;
       
   hPa = groundPressure * (1 - (temperatureGradient * height) / temperature).^5.255;
   density = hPa / (gasConstant * temperature) * 100;   
end