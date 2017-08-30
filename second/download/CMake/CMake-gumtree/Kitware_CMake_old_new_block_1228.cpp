{
      bool done;
      int cc = 0;
      char rpstr[100];
      sprintf(rpstr, "_p_");
      cmSystemTools::ReplaceString(ssin, "+", rpstr);
      std::string sssin = sin;
      do
        {
        done = true;
        for ( it = this->UniqueObjectNamesMap.begin();
              it != this->UniqueObjectNamesMap.end();
              ++ it )
          {
          if ( it->second == ssin )
            {
            done = false;
            }
          }
        if ( done )
          {
          break;
          }
        sssin = ssin;
        cmSystemTools::ReplaceString(ssin, "_p_", rpstr);
        sprintf(rpstr, "_p%d_", cc++);
        }
      while ( !done );
      }