addpath('helpers/');

outputFolder = '../results/raw/';

% iterate all values for entry entry angle(a) and entry speed(v),
% run simulation and dump results in raw format
lift = 0.24;
liftFolder = strcat(outputFolder, sprintf('%0.2f/', lift));
resetFolder(liftFolder);
mkdir(liftFolder);

a = -14.5;
angleFolder = strcat(liftFolder, sprintf('%0.1f/', a));
mkdir(angleFolder);

for v = 4000:500:9000
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

disp('done');

