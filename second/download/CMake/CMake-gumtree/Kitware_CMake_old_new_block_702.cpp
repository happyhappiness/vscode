{
          res += " ";
          res += osvi.szCSDVersion;
          res += " (Build ";
          sprintf(buffer, "%d", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
          }