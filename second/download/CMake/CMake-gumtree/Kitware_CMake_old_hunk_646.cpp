        // write the count into the directory
        std::string fName = dirName;
        fName += "/count.txt";
        FILE *progFile = fopen(fName.c_str(),"w");
        if (progFile)
          {
          fprintf(progFile,"%i\n",count);
