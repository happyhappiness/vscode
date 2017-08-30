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
        sprintf(buffer, "%d", osvi.dwMajorVersion);
        res += buffer;
        res += ".";
        sprintf(buffer, "%d", osvi.dwMinorVersion);
        res += buffer;
        }