        if (lRet == ERROR_SUCCESS)

          {

          res += " Service Pack 6a (Build ";

          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);

          res += buffer;

          res += ")";

          }

