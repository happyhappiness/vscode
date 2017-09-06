kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
{
  kwsys_stl::string res;

#ifdef _WIN32
  char buffer[256];

  OSVERSIONINFOEX osvi;
  BOOL bOsVersionInfoEx;

  // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
  // If that fails, try using the OSVERSIONINFO structure.

  ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

  bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *)&osvi);
  if (!bOsVersionInfoEx)
    {
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx((OSVERSIONINFO *)&osvi)) 
      {
      return 0;
      }
    }
  
  switch (osvi.dwPlatformId)
    {
    // Test for the Windows NT product family.

    case VER_PLATFORM_WIN32_NT:
      
      // Test for the specific product family.

      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
        {
        res += "Microsoft Windows Server 2003 family";
        }

      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
        {
        res += "Microsoft Windows XP";
        }

      if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
        {
        res += "Microsoft Windows 2000";
        }

      if (osvi.dwMajorVersion <= 4)
        {
        res += "Microsoft Windows NT";
        }

      // Test for specific product on Windows NT 4.0 SP6 and later.

      if (bOsVersionInfoEx)
        {
        // Test for the workstation type.

#if (_MSC_VER >= 1300) 
        if (osvi.wProductType == VER_NT_WORKSTATION)
          {
          if (osvi.dwMajorVersion == 4)
            {
            res += " Workstation 4.0";
            }
          else if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
            {
            res += " Home Edition";
            }
          else
            {
            res += " Professional";
            }
          }
            
        // Test for the server type.

        else if (osvi.wProductType == VER_NT_SERVER)
          {
          if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
            {
            if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
              {
              res += " Datacenter Edition";
              }
            else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
              {
              res += " Enterprise Edition";
              }
            else if (osvi.wSuiteMask == VER_SUITE_BLADE)
              {
              res += " Web Edition";
              }
            else
              {
              res += " Standard Edition";
              }
            }
          
          else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
            {
            if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
              {
              res += " Datacenter Server";
              }
            else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
              {
              res += " Advanced Server";
              }
            else
              {
              res += " Server";
              }
            }

          else  // Windows NT 4.0 
            {
            if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
              {
              res += " Server 4.0, Enterprise Edition";
              }
            else
              {
              res += " Server 4.0";
              }
            }
          }
#endif // Visual Studio 7 and up
        }

      // Test for specific product on Windows NT 4.0 SP5 and earlier

      else  
        {
        HKEY hKey;
        #define BUFSIZE 80
        char szProductType[BUFSIZE];
        DWORD dwBufLen=BUFSIZE;
        LONG lRet;

        lRet = RegOpenKeyEx(
          HKEY_LOCAL_MACHINE,
          "SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
          0, KEY_QUERY_VALUE, &hKey);
        if (lRet != ERROR_SUCCESS)
          {
          return 0;
          }

        lRet = RegQueryValueEx(hKey, "ProductType", NULL, NULL,
                               (LPBYTE) szProductType, &dwBufLen);

        if ((lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE))
          {
          return 0;
          }

        RegCloseKey(hKey);

        if (lstrcmpi("WINNT", szProductType) == 0)
          {
          res += " Workstation";
          }
        if (lstrcmpi("LANMANNT", szProductType) == 0)
          {
          res += " Server";
          }
        if (lstrcmpi("SERVERNT", szProductType) == 0)
          {
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
          lstrcmpi(osvi.szCSDVersion, "Service Pack 6") == 0)
        {
        HKEY hKey;
        LONG lRet;

        // Test for SP6 versus SP6a.

        lRet = RegOpenKeyEx(
          HKEY_LOCAL_MACHINE,
          "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009",
          0, KEY_QUERY_VALUE, &hKey);

        if (lRet == ERROR_SUCCESS)
          {
          res += " Service Pack 6a (Build ";
          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
          }
        else // Windows NT 4.0 prior to SP6a
          {
          res += " ";
          res += osvi.szCSDVersion;
          res += " (Build ";
          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
          res += buffer;
          res += ")";
          }
        
        RegCloseKey(hKey);
        }
      else // Windows NT 3.51 and earlier or Windows 2000 and later
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

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
        {
        res += "Microsoft Windows 95";
        if (osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B')
          {
          res += " OSR2";
          }
        }

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
        {
        res += "Microsoft Windows 98";
        if (osvi.szCSDVersion[1] == 'A')
          {
          res += " SE";
          }
        }

      if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
        {
        res += "Microsoft Windows Millennium Edition";
        } 
      break;

    case VER_PLATFORM_WIN32s:
      
      res +=  "Microsoft Win32s";
      break;
    }
#endif

  return res;
}