addpath('helpers/');

outputFolder = '../results/raw/';
resetFolder(outputFolder);

% iterate all values for L/D(l), entry entry angle(a) and entry speed(v),
% run simulation and dump results in raw format
for lift = 0.0:0.05:0.3
    liftFolder = strcat(outputFolder, sprintf('%0.2f/', lift));
    mkdir(liftFolder);
    
    for a = -45:5:-10
        angleFolder = strcat(liftFolder, sprintf('%0.1f/', a));
        mkdir(angleFolder);
        
        for v = 4000:1000:8000
            speedFolder = strcat(angleFolder, sprintf('%d/', v));
            mkdir(speedFolder);
            
            % init and run simulation
            liftToDrag = initConstant(lift);
            angle = initConstant(a);
            speed = initConstant(v);
            tank = initConstant(390);
            
            disp('Starting sim');
            sim('Landing');
            
            dump(speedFolder, 'machSpeed.out', machSpeed);
            dump(speedFolder, 'speed.out', speed);
            dump(speedFolder, 'airSpeed.out', airSpeed);
            dump(speedFolder, 'position.out', position);
            dump(speedFolder, 'acceleration.out', acceleration);
            dump(speedFolder, 'density.out', density);
            dump(speedFolder, 'temperature.out', temperature);
            dump(speedFolder, 'throttle.out', throttle);
            dump(speedFolder, 'thrust.out', thrust);
            dump(speedFolder, 'fuel.out', fuel);  
        end
    end
end

disp('done');