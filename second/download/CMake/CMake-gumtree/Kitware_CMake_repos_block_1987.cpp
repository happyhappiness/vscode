{
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