          res += " ";
          res += osvi.szCSDVersion;
          res += " (Build ";
          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
          }
