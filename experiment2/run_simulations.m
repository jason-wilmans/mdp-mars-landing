addpath('helpers/');

outputFolder = '../results/raw/';

%resetFolder(outputFolder);

% iterate all values for L/D(l), entry entry angle(a) and entry speed(v),
% run simulation and dump results in raw format
for lift = 0.0:0.01:0.0    
    liftFolder = strcat(outputFolder, sprintf('%0.2f/', lift));
    mkdir(liftFolder);
    
    for a = -20:5:-10
        angleFolder = strcat(liftFolder, sprintf('%0.1f/', a));
        mkdir(angleFolder);
        
        for v = 4000:1000:9000
            speedFolder = strcat(angleFolder, sprintf('%d/', v));
            mkdir(speedFolder);
            
            % init and run simulation
            liftToDrag = initConstant(lift);
            angle = initConstant(a);
            speed = initConstant(v);
            disp('Starting sim');
            sim('Landing');
            
            dump(speedFolder, 'speed.out', speed);
            dump(speedFolder, 'airSpeed.out', airSpeed);
            dump(speedFolder, 'position.out', position);
            dump(speedFolder, 'acceleration.out', acceleration);            
        end
    end
end

disp('done');