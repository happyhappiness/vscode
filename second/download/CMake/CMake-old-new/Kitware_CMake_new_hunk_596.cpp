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
