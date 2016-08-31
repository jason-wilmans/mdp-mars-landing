function dump( path, filename, array )
    full = strcat(path, filename);
    fileID = fopen(full, 'w');
    fprintf(fileID, '%e\n', array);
    fclose(fileID);
end