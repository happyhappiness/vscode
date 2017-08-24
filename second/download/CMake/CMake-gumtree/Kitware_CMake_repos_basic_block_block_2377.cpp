{
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
      }