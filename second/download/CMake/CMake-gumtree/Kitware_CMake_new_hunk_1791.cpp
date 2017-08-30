      struct stat statinfo;

      GetModuleFileName(NULL, modulepath, sizeof(modulepath));

      for (i = x = 0; modulepath[i]; i++)

        if (modulepath[i] == '\\')

          x = i+1;

      modulepath[x] = '\0';

      /* Create the full-name to w9xpopen, so we can test it exists */

      strncat(modulepath, 

              szConsoleSpawn, 

              (sizeof(modulepath)/sizeof(modulepath[0]))

              -strlen(modulepath));

      if (stat(modulepath, &statinfo) != 0) 

        {

          /* Eeek - file-not-found - possibly an embedding 

             situation - see if we can locate it in sys.prefix 

          */

        strncpy(modulepath, 

                ".", 

                sizeof(modulepath)/sizeof(modulepath[0]));

        if (modulepath[strlen(modulepath)-1] != '\\')

          strcat(modulepath, "\\");

        strncat(modulepath, 

                szConsoleSpawn, 

                (sizeof(modulepath)/sizeof(modulepath[0]))

                -strlen(modulepath));

        /* No where else to look - raise an easily identifiable

           error, rather than leaving Windows to report

           "file not found" - as the user is probably blissfully

           unaware this shim EXE is used, and it will confuse them.

           (well, it confused me for a while ;-)

        */

        if (stat(modulepath, &statinfo) != 0) 

          {

          std::cout 

            << "Can not locate '" << modulepath

            << "' which is needed "

            "for popen to work with your shell "

            "or platform." << std::endl;

          return FALSE;

          }

        }

      x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +

        (int)strlen(modulepath) + 

        (int)strlen(szConsoleSpawn) + 1;



      s2 = (char *)_alloca(x);

      ZeroMemory(s2, x);

      sprintf(

        s2,

        "%s %s%s%s",

        modulepath,

        s1,

        s3,

        cmdstring);

      sprintf(

        s2,

        "%s %s",

        modulepath,

        cmdstring);

      }

    }



