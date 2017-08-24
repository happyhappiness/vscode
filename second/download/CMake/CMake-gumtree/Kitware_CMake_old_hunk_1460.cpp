      // set the run var
      char retChar[1000];
      sprintf(retChar,"%i",retVal);
      m_Makefile->AddDefinition(argv[1].c_str(), retChar);
      }
    else
      {
      cmSystemTools::Error("Unable to find executable for TRY_RUN");
      }
    }
  
