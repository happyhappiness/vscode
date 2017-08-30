        // write the count into the directory

        std::string fName = dirName;

        fName += "/count.txt";

        FILE *progFile = cmsys::SystemTools::Fopen(fName.c_str(),"w");

        if (progFile)

          {

          fprintf(progFile,"%i\n",count);

