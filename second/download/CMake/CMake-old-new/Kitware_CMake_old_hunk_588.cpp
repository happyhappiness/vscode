    // Command to report progress for a build
    else if (args[1] == "cmake_progress_report" && args.size() >= 3)
      {
      std::string dirName = args[2];
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
        return 0;
        }
      else
        {
        if (1!=fscanf(progFile,"%i",&count))
          {
          cmSystemTools::Message("Could not read from progress file.");
          }
        fclose(progFile);
        }
      unsigned int i;
      for (i = 3; i < args.size(); ++i)
        {
        fName = dirName;
        fName += "/";
        fName += args[i];
        progFile = cmsys::SystemTools::Fopen(fName,"w");
        if (progFile)
          {
          fprintf(progFile,"empty");
          fclose(progFile);
          }
        }
      int fileNum = static_cast<int>
        (cmsys::Directory::GetNumberOfFilesInDirectory(dirName));
      if (count > 0)
        {
        // print the progress
        fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
        }
      return 0;
      }

