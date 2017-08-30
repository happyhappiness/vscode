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

