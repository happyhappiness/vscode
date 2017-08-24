(osvi.dwMajorVersion == 5) {
            if (osvi.wSuiteMask & VER_SUITE_PERSONAL) {
              res += " Home Edition";
            } else {
              res += " Professional";
            }
          }