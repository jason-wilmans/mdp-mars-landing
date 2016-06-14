function [ airDrag, density ] = AirDrag( speed, rocketDiameter, mass, height, parachuteDeployed )    
    density = Density(height);
    
    area = Area(rocketDiameter, parachuteDeployed);
    cw = DragCoefficient(speed, parachuteDeployed);
       
    airDrag = (0.5 * cw * area * density * speed * speed) / mass;     
end

function [ area ] = Area( rocketDiameter, parachuteDeployed)
    if parachuteDeployed
        diameter = 33.528;
    else
        diameter = rocketDiameter;
    end
    
    area = (3.14195 * diameter * diameter) / 4;
end

function [ cw ] = DragCoefficient(speed, parachuteDeployed)
    % parachute overrides everything. Else, direction of movement is
    % relevant: moving down the rocjet hits with the exhaust, upwards with
    % it's tip. Also the direction of the force is opposite of the
    % movement.
    
    if (parachuteDeployed)
        cw = 1.33; % parachute approximation
    else       
        if speed >= 0
            cw = 0.1; % better than convex half sphere (approximation of rocket tip)            
        else
            cw = 1.10; % concave half sphere (approximation of jet outlet)        
        end
    end
    
    if speed >= 0
        cw = -cw;
    end
end

function [ density ] = Density( height )
% result is gas density in kg * m^3
   
    % earth    
    % (https://de.wikipedia.org/wiki/Gaskonstante#Spezifische_Gaskonstante)
	% gasConstant = 287.058;
    % 15�C in K, (international standard atmosphere, https://de.wikipedia.org/wiki/Barometrische_H�henformel)
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
       
    
   heightCoefficient = (1 - (temperatureGradient * height) / temperature);
   hPa = groundPressure * max(heightCoefficient, 0).^5.255;
   density = hPa / (gasConstant * temperature) * 100;   
end