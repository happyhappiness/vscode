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