msg << "FilesDiffer failed to read files (allocated: " 
        << statSource.st_size << ", read source: " <<  finSource.gcount() 
        << ", read dest: " << finDestination.gcount() << std::ends;