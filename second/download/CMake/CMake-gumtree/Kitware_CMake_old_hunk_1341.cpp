      {

      fprintf(stderr, "Checking file [%s]\n", file.c_str());

      }

    if(cmSystemTools::FileExists(file.c_str(), true))

      {

      return true;

      }

