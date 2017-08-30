      // set the run var

      char retChar[1000];

      sprintf(retChar,"%i",retVal);

      m_Makefile->AddDefinition(argv[0].c_str(), retChar);

      }

    }

  

