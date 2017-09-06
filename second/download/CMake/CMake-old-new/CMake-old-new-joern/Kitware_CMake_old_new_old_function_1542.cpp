void cmSystemTools::cmCopyFile(const char* source,
                               const char* destination)
{
  const int bufferSize = 4096;
  char buffer[bufferSize];

  // If destination is a directory, try to create a file with the same
  // name as the source in that directory.

  std::string new_destination;
  if(cmSystemTools::FileExists(destination) &&
     cmSystemTools::FileIsDirectory(destination))
    {
    new_destination = destination;
    cmSystemTools::ConvertToUnixSlashes(new_destination);
    new_destination += '/';
    std::string source_name = source;
    new_destination += cmSystemTools::GetFilenameName(source_name);
    destination = new_destination.c_str();
    }

  // Create destination directory

  std::string destination_dir = destination;
  destination_dir = cmSystemTools::GetFilenamePath(destination_dir);
  cmSystemTools::MakeDirectory(destination_dir.c_str());

  // Open files

#if defined(_WIN32) || defined(__CYGWIN__)
  std::ifstream fin(source, 
                    std::ios::binary | std::ios::in);
#else
  std::ifstream fin(source);
#endif
  if(!fin)
    {
    cmSystemTools::Error("CopyFile failed to open input file \"",
                         source, "\"");
    return;
    }

#if defined(_WIN32) || defined(__CYGWIN__)
  std::ofstream fout(destination, 
                     std::ios::binary | std::ios::out | std::ios::trunc);
#else
  std::ofstream fout(destination, 
                     std::ios::out | std::ios::trunc);
#endif
  if(!fout)
    {
    cmSystemTools::Error("CopyFile failed to open output file \"",
                         destination, "\"");
    return;
    }
  
  // This copy loop is very sensitive on certain platforms with
  // slightly broken stream libraries (like HPUX).  Normally, it is
  // incorrect to not check the error condition on the fin.read()
  // before using the data, but the fin.gcount() will be zero if an
  // error occurred.  Therefore, the loop should be safe everywhere.
  while(fin)
    {
    fin.read(buffer, bufferSize);
    if(fin.gcount())
      {
      fout.write(buffer, fin.gcount());
      }
    }

  fin.close();
  fout.close();

  // More checks

  struct stat statSource, statDestination;
  if (stat(source, &statSource) != 0 ||
      stat(destination, &statDestination) != 0)
    {
    cmSystemTools::Error("CopyFile failed to copy files!");
    }

  if (statSource.st_size != statDestination.st_size)
    {
    char msg[256];
    sprintf(msg, "CopyFile failed to copy files (sizes differ, source: %lu, dest: %lu)", statSource.st_size, statDestination.st_size);
    cmSystemTools::Error(msg);
    }
}