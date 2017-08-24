(osvi.dwMajorVersion <= 4) // Windows NT 4.0
          {
            if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) {
              res += " Server 4.0, Enterprise Edition";
            } else {
              res += " Server 4.0";
            }
          }