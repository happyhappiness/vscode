bool SystemInformationImplementation::QueryOSInformation()
{
#if defined(_WIN32)

  this->OSName = "Windows";

  OSVERSIONINFOEXW osvi;
  BOOL bIsWindows64Bit;
  BOOL bOsVersionInfoEx;
  char operatingSystem[256];

  // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
  ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXW));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
#ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
#pragma warning(push)
#ifdef __INTEL_COMPILER
#pragma warning(disable : 1478)
#else
#pragma warning(disable : 4996)
#endif
#endif
  bOsVersionInfoEx = GetVersionExW((OSVERSIONINFOW*)&osvi);
  if (!bOsVersionInfoEx) {
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
    if (!GetVersionExW((OSVERSIONINFOW*)&osvi)) {
      return false;
    }
  }
#ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
#pragma warning(pop)
#endif

  switch (osvi.dwPlatformId) {
    case VER_PLATFORM_WIN32_NT:
      // Test for the product.
      if (osvi.dwMajorVersion <= 4) {
        this->OSRelease = "NT";
      }
      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0) {
        this->OSRelease = "2000";
      }
      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) {
        this->OSRelease = "XP";
      }
      // XP Professional x64
      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2) {
        this->OSRelease = "XP";
      }
#ifdef VER_NT_WORKSTATION
      // Test for product type.
      if (bOsVersionInfoEx) {
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
      } else
#endif // VER_NT_WORKSTATION
      {
        HKEY hKey;
        wchar_t szProductType[80];
        DWORD dwBufLen;

        // Query the registry to retrieve information.
        RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0,
                      KEY_QUERY_VALUE, &hKey);
        RegQueryValueExW(hKey, L"ProductType", NULL, NULL,
                         (LPBYTE)szProductType, &dwBufLen);
        RegCloseKey(hKey);

        if (lstrcmpiW(L"WINNT", szProductType) == 0) {
          this->OSRelease += " Professional";
        }
        if (lstrcmpiW(L"LANMANNT", szProductType) == 0) {
          // Decide between Windows 2000 Advanced Server and Windows .NET
          // Enterprise Server.
          if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) {
            this->OSRelease += " Standard Server";
          } else {
            this->OSRelease += " Server";
          }
        }
        if (lstrcmpiW(L"SERVERNT", szProductType) == 0) {
          // Decide between Windows 2000 Advanced Server and Windows .NET
          // Enterprise Server.
          if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) {
            this->OSRelease += " Enterprise Server";
          } else {
            this->OSRelease += " Advanced Server";
          }
        }
      }

      // Display version, service pack (if any), and build number.
      if (osvi.dwMajorVersion <= 4) {
        // NB: NT 4.0 and earlier.
        sprintf(operatingSystem, "version %ld.%ld %ls (Build %ld)",
                osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.szCSDVersion,
                osvi.dwBuildNumber & 0xFFFF);
        this->OSVersion = operatingSystem;
      } else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) {
        // Windows XP and .NET server.
        typedef BOOL(CALLBACK * LPFNPROC)(HANDLE, BOOL*);
        HINSTANCE hKernelDLL;
        LPFNPROC DLLProc;

        // Load the Kernel32 DLL.
        hKernelDLL = LoadLibraryW(L"kernel32");
        if (hKernelDLL != NULL) {
          // Only XP and .NET Server support IsWOW64Process so... Load
          // dynamically!
          DLLProc = (LPFNPROC)GetProcAddress(hKernelDLL, "IsWow64Process");

          // If the function address is valid, call the function.
          if (DLLProc != NULL)
            (DLLProc)(GetCurrentProcess(), &bIsWindows64Bit);
          else
            bIsWindows64Bit = false;

          // Free the DLL module.
          FreeLibrary(hKernelDLL);
        }
      } else {
        // Windows 2000 and everything else.
        sprintf(operatingSystem, "%ls (Build %ld)", osvi.szCSDVersion,
                osvi.dwBuildNumber & 0xFFFF);
        this->OSVersion = operatingSystem;
      }
      break;

    case VER_PLATFORM_WIN32_WINDOWS:
      // Test for the product.
      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0) {
        this->OSRelease = "95";
        if (osvi.szCSDVersion[1] == 'C') {
          this->OSRelease += "OSR 2.5";
        } else if (osvi.szCSDVersion[1] == 'B') {
          this->OSRelease += "OSR 2";
        }
      }

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10) {
        this->OSRelease = "98";
        if (osvi.szCSDVersion[1] == 'A') {
          this->OSRelease += "SE";
        }
      }

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90) {
        this->OSRelease = "Me";
      }
      break;

    case VER_PLATFORM_WIN32s:
      this->OSRelease = "Win32s";
      break;

    default:
      this->OSRelease = "Unknown";
      break;
  }

  // Get the hostname
  WORD wVersionRequested;
  WSADATA wsaData;
  char name[255];
  wVersionRequested = MAKEWORD(2, 0);

  if (WSAStartup(wVersionRequested, &wsaData) == 0) {
    gethostname(name, sizeof(name));
    WSACleanup();
  }
  this->Hostname = name;

  const char* arch = getenv("PROCESSOR_ARCHITECTURE");
  const char* wow64 = getenv("PROCESSOR_ARCHITEW6432");
  if (arch) {
    this->OSPlatform = arch;
  }

  if (wow64) {
    // the PROCESSOR_ARCHITEW6432 is only defined when running 32bit programs
    // on 64bit OS
    this->OSIs64Bit = true;
  } else if (arch) {
    // all values other than x86 map to 64bit architectures
    this->OSIs64Bit = (strncmp(arch, "x86", 3) != 0);
  }

#else

  struct utsname unameInfo;
  int errorFlag = uname(&unameInfo);
  if (errorFlag == 0) {
    this->OSName = unameInfo.sysname;
    this->Hostname = unameInfo.nodename;
    this->OSRelease = unameInfo.release;
    this->OSVersion = unameInfo.version;
    this->OSPlatform = unameInfo.machine;

    // This is still insufficient to capture 64bit architecture such
    // powerpc and possible mips and sparc
    if (this->OSPlatform.find_first_of("64") != std::string::npos) {
      this->OSIs64Bit = true;
    }
  }

#ifdef __APPLE__
  this->OSName = "Unknown Apple OS";
  this->OSRelease = "Unknown product version";
  this->OSVersion = "Unknown build version";

  this->CallSwVers("-productName", this->OSName);
  this->CallSwVers("-productVersion", this->OSRelease);
  this->CallSwVers("-buildVersion", this->OSVersion);
#endif

#endif

  return true;
}