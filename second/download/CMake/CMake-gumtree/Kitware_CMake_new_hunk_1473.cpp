  if(statSource.st_size != finSource.gcount() ||
     statSource.st_size != finDestination.gcount())
    {
    std::strstream msg;
    msg << "FilesDiffer failed to read files (allocated: " 
        << statSource.st_size << ", read source: " <<  finSource.gcount() 
        << ", read dest: " << finDestination.gcount() << std::ends;
    cmSystemTools::Error(msg.str());
    delete [] msg.str();
    delete [] source_buf;
    delete [] dest_buf;
    return false;
    }
  int ret = memcmp((const void*)source_buf, 
                   (const void*)dest_buf, 
                   statSource.st_size);
