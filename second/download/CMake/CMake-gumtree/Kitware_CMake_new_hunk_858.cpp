        fName = dirName;

        fName += "/";

        fName += args[i];

        progFile = cmsys::SystemTools::Fopen(fName.c_str(),"w");

        if (progFile)

          {

          fprintf(progFile,"empty");

