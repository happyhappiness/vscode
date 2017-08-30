      std::string dirName = args[2];

      dirName += "/Progress";

      cmSystemTools::RemoveADirectory(dirName.c_str());

      int count = atoi(args[3].c_str());

      if (count)

        {

        cmSystemTools::MakeDirectory(dirName.c_str());

        // write the count into the directory

        std::string fName = dirName;

        fName += "/count.txt";

        FILE *progFile = fopen(fName.c_str(),"w");

        if (progFile)

          {

          fprintf(progFile,"%i\n",count);

          fclose(progFile);

          }

        }

      return 0;

      }

