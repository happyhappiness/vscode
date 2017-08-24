            << "Can not locate '" << modulepath
            << "' which is needed "
            "for popen to work with your shell "
            "or platform." << std::endl;    
          free(s1);
          free(s2);
          return FALSE;
          }
        }
      x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +
        (int)strlen(modulepath) + 
        (int)strlen(szConsoleSpawn) + 1;
      if(s2)
        {
        free(s2);
        }
      s2 = (char *)malloc(x);
      ZeroMemory(s2, x);
      sprintf(
        s2,
