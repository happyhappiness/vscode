        }

      int fileNum = static_cast<int>

        (cmsys::Directory::GetNumberOfFilesInDirectory(dirName.c_str()));

      // read the count

      fName = dirName;

      fName += "/count.txt";

      progFile = fopen(fName.c_str(),"r");

      if (progFile)

        {

        int count = 0;

        fscanf(progFile,"%i",&count);

        if (count > 0)

          {

          // print the progress

          fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);

          }

        fclose(progFile);

        }

      return 0;

      }
