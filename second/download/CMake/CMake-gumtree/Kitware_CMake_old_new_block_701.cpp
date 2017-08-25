{
          res += " Service Pack 6a (Build ";
          sprintf(buffer, "%d", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
          }