addpath('helpers/');

mdl = 'Landing';
load_system(mdl);

angle = initConstant(-14.8);
speed = initConstant(5630);
sim(mdl);

fileID = fopen('myfile.txt','w');
fprintf(fileID, '%4.2f\n', airSpeed);
fclose(fileID);
disp('done');