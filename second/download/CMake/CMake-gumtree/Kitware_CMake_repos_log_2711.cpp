sprintf(operatingSystem, "version %ld.%ld %ls (Build %ld)",
                osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.szCSDVersion,
                osvi.dwBuildNumber & 0xFFFF)