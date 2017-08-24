(osvi.wProductType == VER_NT_SERVER) {
          if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2) {
            if (osvi.wSuiteMask & VER_SUITE_DATACENTER) {
              res += " Datacenter Edition";
            } else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) {
              res += " Enterprise Edition";
            } else if (osvi.wSuiteMask == VER_SUITE_BLADE) {
              res += " Web Edition";
            } else {
              res += " Standard Edition";
            }
          }

          else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0) {
            if (osvi.wSuiteMask & VER_SUITE_DATACENTER) {
              res += " Datacenter Server";
            } else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) {
              res += " Advanced Server";
            } else {
              res += " Server";
            }
          }

          else if (osvi.dwMajorVersion <= 4) // Windows NT 4.0
          {
            if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) {
              res += " Server 4.0, Enterprise Edition";
            } else {
              res += " Server 4.0";
            }
          }
        }