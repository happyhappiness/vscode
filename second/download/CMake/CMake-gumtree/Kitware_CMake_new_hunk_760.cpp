}

//----------------------------------------------------------------------------
static void cmcmdProgressReport(std::string const& dir,
                                std::string const& num)
{
  std::string dirName = dir;
  dirName += "/Progress";
  std::string fName;
  FILE *progFile;

  // read the count
  fName = dirName;
  fName += "/count.txt";
  progFile = cmsys::SystemTools::Fopen(fName,"r");
  int count = 0;
  if (!progFile)
    {
    return;
    }
  else
    {
    if (1!=fscanf(progFile,"%i",&count))
      {
      cmSystemTools::Message("Could not read from progress file.");
      }
    fclose(progFile);
    }
  const char* last = num.c_str();
  for(const char* c = last;; ++c)
    {
    if (*c == ',' || *c == '\0')
      {
      if (c != last)
        {
        fName = dirName;
        fName += "/";
        fName.append(last, c-last);
        progFile = cmsys::SystemTools::Fopen(fName,"w");
        if (progFile)
          {
          fprintf(progFile,"empty");
          fclose(progFile);
          }
        }
      if(*c == '\0')
        {
        break;
        }
      last = c + 1;
      }
    }
  int fileNum = static_cast<int>
    (cmsys::Directory::GetNumberOfFilesInDirectory(dirName));
  if (count > 0)
    {
    // print the progress
    fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
    }
}

//----------------------------------------------------------------------------
int cmcmd::ExecuteEchoColor(std::vector<std::string>& args)
{
  // The arguments are
