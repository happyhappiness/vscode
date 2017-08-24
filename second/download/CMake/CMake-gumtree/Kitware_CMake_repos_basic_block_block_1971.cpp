(osvi.wProductType == VER_NT_SERVER) {
          // Check for .NET Server instead of Windows XP.
          if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) {
            this->OSRelease = ".NET";
          }

          // Continue with the type detection.
          if (osvi.wSuiteMask & VER_SUITE_DATACENTER) {
            this->OSRelease += " DataCenter Server";
          } else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) {
            this->OSRelease += " Advanced Server";
          } else {
            this->OSRelease += " Server";
          }
        }