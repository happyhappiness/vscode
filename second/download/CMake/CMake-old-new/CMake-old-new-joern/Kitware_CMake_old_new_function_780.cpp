bool cmSystemTools::FilesDiffer(const char* source,
                                const char* destination)
{
  struct stat statSource;
  if (stat(source, &statSource) != 0) 
    {
    return true;
    }

  struct stat statDestination;
  if (stat(destination, &statDestination) != 0) 
    {
    return true;
    }

  if(statSource.st_size != statDestination.st_size)
    {
    return true;
    }

  if(statSource.st_size == 0)
    {
    return false;
    }

#if defined(_WIN32) || defined(__CYGWIN__)
  std::ifstream finSource(source, 
                          std::ios::binary | std::ios::in);
  std::ifstream finDestination(destination, 
                               std::ios::binary | std::ios::in);
#else
  std::ifstream finSource(source);
  std::ifstream finDestination(destination);
#endif
  if(!finSource || !finDestination)
    {
    return true;
    }

  char* source_buf = new char[statSource.st_size];
  char* dest_buf = new char[statSource.st_size];

  finSource.read(source_buf, statSource.st_size);
  finDestination.read(dest_buf, statSource.st_size);

  if(statSource.st_size != finSource.gcount() ||
     statSource.st_size != finDestination.gcount())
    {
    char msg[256];
    sprintf(msg, "FilesDiffer failed to read files (allocated: %lu, source: %lu, dest: %lu)", statSource.st_size, finSource.gcount(), finDestination.gcount());
    cmSystemTools::Error(msg);
    delete [] source_buf;
    delete [] dest_buf;
    return false;
    }

  finSource.close();
  finDestination.close();

  int ret = memcmp((const void*)source_buf, 
                   (const void*)dest_buf, 
                   statSource.st_size);

  delete [] dest_buf;
  delete [] source_buf;

  return ret != 0;
}