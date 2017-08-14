std::string SystemTools::GetOperatingSystemNameAndVersion()
{
  std::string res;

#ifdef _WIN32
  char buffer[256];

  OSVERSIONINFOEXA osvi;
  BOOL bOsVersionInfoEx;

  ZeroMemory(&osvi, sizeof(osvi));
  osvi.dwOSVersionInfoSize = sizeof(osvi);

#ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
#pragma warning(push)
#ifdef __INTEL_COMPILER
#pragma warning(disable : 1478)
#else
#pragma warning(disable : 4996)
#endif
#endif
  bOsVersionInfoEx = GetVersionExA((OSVERSIONINFOA*)&osvi);
  if (!bOsVersionInfoEx) {
    return 0;
  }
#ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
#pragma warning(pop)
#endif

  switch (osvi.dwPlatformId) {
    // Test for the Windows NT product family.

    case VER_PLATFORM_WIN32_NT:

      // Test for the specific product family.
      if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0) {
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          res += "Microsoft Windows 10";
        } else {
          res += "Microsoft Windows Server 2016 family";
        }
      }

      if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3) {
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          res += "Microsoft Windows 8.1";
        } else {
          res += "Microsoft Windows Server 2012 R2 family";
        }
      }

      if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2) {
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          res += "Microsoft Windows 8";
        } else {
          res += "Microsoft Windows Server 2012 family";
        }
      }

      if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1) {
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          res += "Microsoft Windows 7";
        } else {
          res += "Microsoft Windows Server 2008 R2 family";
        }
      }

      if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0) {
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          res += "Microsoft Windows Vista";
        } else {
          res += "Microsoft Windows Server 2008 family";
        }
      }

      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2) {
        res += "Microsoft Windows Server 2003 family";
      }

      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) {
        res += "Microsoft Windows XP";
      }

      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0) {
        res += "Microsoft Windows 2000";
      }

      if (osvi.dwMajorVersion <= 4) {
        res += "Microsoft Windows NT";
      }

      // Test for specific product on Windows NT 4.0 SP6 and later.

      if (bOsVersionInfoEx) {
        // Test for the workstation type.

        if (osvi.wProductType == VER_NT_WORKSTATION) {
          if (osvi.dwMajorVersion == 4) {
            res += " Workstation 4.0";
          } else if (osvi.dwMajorVersion == 5) {
            if (osvi.wSuiteMask & VER_SUITE_PERSONAL) {
              res += " Home Edition";
            } else {
              res += " Professional";
            }
          }
        }

        // Test for the server type.

        else if (osvi.wProductType == VER_NT_SERVER) {
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
      }

      // Test for specific product on Windows NT 4.0 SP5 and earlier

      else {
        HKEY hKey;
#define BUFSIZE 80
        wchar_t szProductType[BUFSIZE];
        DWORD dwBufLen = BUFSIZE;
        LONG lRet;

        lRet =
          RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                        L"SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
                        0, KEY_QUERY_VALUE, &hKey);
        if (lRet != ERROR_SUCCESS) {
          return 0;
        }

        lRet = RegQueryValueExW(hKey, L"ProductType", NULL, NULL,
                                (LPBYTE)szProductType, &dwBufLen);

        if ((lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE)) {
          return 0;
        }

        RegCloseKey(hKey);

        if (lstrcmpiW(L"WINNT", szProductType) == 0) {
          res += " Workstation";
        }
        if (lstrcmpiW(L"LANMANNT", szProductType) == 0) {
          res += " Server";
        }
        if (lstrcmpiW(L"SERVERNT", szProductType) == 0) {
          res += " Advanced Server";
        }

        res += " ";
        sprintf(buffer, "%ld", osvi.dwMajorVersion);
        res += buffer;
        res += ".";
        sprintf(buffer, "%ld", osvi.dwMinorVersion);
        res += buffer;
      }

      // Display service pack (if any) and build number.

      if (osvi.dwMajorVersion == 4 &&
          lstrcmpiA(osvi.szCSDVersion, "Service Pack 6") == 0) {
        HKEY hKey;
        LONG lRet;

        // Test for SP6 versus SP6a.

        lRet = RegOpenKeyExW(
          HKEY_LOCAL_MACHINE,
          L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009",
          0, KEY_QUERY_VALUE, &hKey);

        if (lRet == ERROR_SUCCESS) {
          res += " Service Pack 6a (Build ";
          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
        } else // Windows NT 4.0 prior to SP6a
        {
          res += " ";
          res += osvi.szCSDVersion;
          res += " (Build ";
          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
        }

        RegCloseKey(hKey);
      } else // Windows NT 3.51 and earlier or Windows 2000 and later
      {
        res += " ";
        res += osvi.szCSDVersion;
        res += " (Build ";
        sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
        res += buffer;
        res += ")";
      }

      break;

    // Test for the Windows 95 product family.

    case VER_PLATFORM_WIN32_WINDOWS:

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0) {
        res += "Microsoft Windows 95";
        if (osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B') {
          res += " OSR2";
        }
      }

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10) {
        res += "Microsoft Windows 98";
        if (osvi.szCSDVersion[1] == 'A') {
          res += " SE";
        }
      }

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90) {
        res += "Microsoft Windows Millennium Edition";
      }
      break;

    case VER_PLATFORM_WIN32s:

      res += "Microsoft Win32s";
      break;
  }
#endif

  return res;
}