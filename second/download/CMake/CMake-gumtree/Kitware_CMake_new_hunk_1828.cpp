
  if (statSource.st_size != statDestination.st_size)
    {
    std::strstream msg;
    msg << "CopyFile failed to copy files (sizes differ, source: " 
        << statSource.st_size << " , dest: " << statDestination.st_size 
        << std::ends;
    cmSystemTools::Error(msg.str());
    delete [] msg.str();
    }
}
