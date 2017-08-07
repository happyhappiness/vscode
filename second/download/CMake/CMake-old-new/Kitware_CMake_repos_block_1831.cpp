{
        // Windows 2000 and everything else.
        sprintf(operatingSystem, "%ls (Build %ld)", osvi.szCSDVersion,
                osvi.dwBuildNumber & 0xFFFF);
        this->OSVersion = operatingSystem;
      }