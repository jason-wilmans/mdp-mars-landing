addpath('helpers/');

outputFolder = '../results/raw/';
resetFolder(outputFolder);

% iterate all values for L/D(l), entry entry angle(a) and entry speed(v),
% run simulation and dump results in raw format
for lift = 0.24:0.05:0.24    
    liftFolder = strcat(outputFolder, sprintf('%0.2f/', lift));
    mkdir(liftFolder);
    
    for a = -14.5:5:-14.5
        angleFolder = strcat(liftFolder, sprintf('%0.1f/', a));
        mkdir(angleFolder);
        
        for v = 5630:2000:5630
            speedFolder = strcat(angleFolder, sprintf('%d/', v));
            mkdir(speedFolder);
            
            % init and run simulation
            liftToDrag = initConstant(lift);
            angle = initConstant(a);
            speed = initConstant(v);
            tank = initConstant(390);
            
            disp('Starting sim');
            sim('Landing');
            
            dump(speedFolder, 'speed.out', speed);            
            dump(speedFolder, 'airSpeed.out', airSpeed);
            dump(speedFolder, 'machSpeed.out', density);
            dump(speedFolder, 'position.out', position);
            dump(speedFolder, 'acceleration.out', acceleration);            
        end
    end
end

disp('done');