msg << "CopyFile failed to copy files (sizes differ, source: " 
        << statSource.st_size << " , dest: " << statDestination.st_size 
        << std::ends;