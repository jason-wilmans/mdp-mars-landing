function dump( path, filename, array )
    full = strcat(path, filename);
    fileID = fopen(full, 'w');
    fprintf(fileID, '%6.3f\n', array);
    fclose(fileID);
end

