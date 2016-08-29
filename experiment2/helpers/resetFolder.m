function resetFolder( path )
    if exist(path, 'dir')
        rmdir(path, 's');
    end
    
    mkdir(path);
end

