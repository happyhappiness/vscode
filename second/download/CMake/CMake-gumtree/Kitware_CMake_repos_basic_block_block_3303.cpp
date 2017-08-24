(ISFLAG("--stdout"))            srcMode          = SM_F2O;  else
      if (ISFLAG("--decompress"))        opMode           = OM_UNZ;  else
      if (ISFLAG("--compress"))          opMode           = OM_Z;    else
      if (ISFLAG("--force"))             forceOverwrite   = True;    else
      if (ISFLAG("--test"))              opMode           = OM_TEST; else
      if (ISFLAG("--keep"))              keepInputFiles   = True;    else
      if (ISFLAG("--small"))             smallMode        = True;    else
      if (ISFLAG("--quiet"))             noisy            = False;   else
      if (ISFLAG("--version"))           license();                  else
      if (ISFLAG("--license"))           license();                  else
      if (ISFLAG("--exponential"))       workFactor = 1;             else 
      if (ISFLAG("--repetitive-best"))   redundant(aa->name);        else
      if (ISFLAG("--repetitive-fast"))   redundant(aa->name);        else
      if (ISFLAG("--fast"))              blockSize100k = 1;          else
      if (ISFLAG("--best"))              blockSize100k = 9;          else
      if (ISFLAG("--verbose"))           verbosity++;                else
      if (ISFLAG("--help"))              { usage ( progName ); exit ( 0 ); }
         else
         if (strncmp ( aa->name, "--", 2) == 0) {
            fprintf ( stderr, "%s: Bad flag `%s'\n", progName, aa->name );
            usage ( progName );
            exit ( 1 );
         }