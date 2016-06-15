function [ airDrag, density ] = AirDrag( speed, rocketDiameter, mass, height, parachuteDeployed )    
      
    area = Area(rocketDiameter, parachuteDeployed);
    cw = DragCoefficient(speed, parachuteDeployed);

    pressure = Pressure(height);
    density = ToDensity(pressure);
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

function [ pressure ] = Pressure( height )
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
       
    
   % heightCoefficient = (1 - (temperatureGradient * height) / temperature);
   % hPa = groundPressure * max(heightCoefficient, 0).^5.255;
   %density = hPa / (gasConstant * temperature) * 100;   
   
   height = 0;
   if height >= 7000
       T = -31 - 0.000998 * height;
       p = 0.699 * exp(-0.00009 * height);
   else
       T = -23.4 - 0.00222 * height;
       p = .699 * exp(-0.00009 * height);
   end
   
   pressure = p / (0.1921 * (T + 273.1)) * 1000;
end

function [ density ] = ToDensity(pressure)
    molMass = 0.0440095;
    co2GasConstant = 191.5204402;
    temp = 218.0;
    density = (pressure * molMass) / (co2GasConstant * temp);
    
end