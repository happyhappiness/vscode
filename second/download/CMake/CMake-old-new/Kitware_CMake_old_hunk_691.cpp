        fName = dirName;
        fName += "/";
        fName += args[i];
        progFile = fopen(fName.c_str(),"w");
        if (progFile)
          {
          fprintf(progFile,"empty");
