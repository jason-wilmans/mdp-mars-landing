function [ airDrag, density ] = AirDrag( speed, rocketDiameter, mass, height, parachuteDeployed )    
      
    area = Area(rocketDiameter, parachuteDeployed);
    cw = DragCoefficient(speed, parachuteDeployed);

    %height = 0;
    density = Density(height);    
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
    % relevant: moving down the rocket hits with the exhaust, upwards with
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
   
   p = 0.699 * exp(-0.00009 * height);
   
   if height > 7000
       T = -31 - 0.000998 * height;       
   else
       T = -23.4 - 0.00222 * height;       
   end
   
   density = p / (0.1921 * (T + 273.1));   
end