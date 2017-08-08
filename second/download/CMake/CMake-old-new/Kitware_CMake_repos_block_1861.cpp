{
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0) {
            this->OSRelease = "Vista";
          }
          if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1) {
            this->OSRelease = "7";
          }
// VER_SUITE_PERSONAL may not be defined
#ifdef VER_SUITE_PERSONAL
          else {
            if (osvi.wSuiteMask & VER_SUITE_PERSONAL) {
              this->OSRelease += " Personal";
            } else {
              this->OSRelease += " Professional";
            }
          }
#endif
        } else if (osvi.wProductType == VER_NT_SERVER) {
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

        sprintf(operatingSystem, "%ls (Build %ld)", osvi.szCSDVersion,
                osvi.dwBuildNumber & 0xFFFF);
        this->OSVersion = operatingSystem;
      }