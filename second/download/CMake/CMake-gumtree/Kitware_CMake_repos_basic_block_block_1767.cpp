{
    HKEY hKey = NULL;
    LONG err =
      RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                    L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
                    KEY_READ, &hKey);

    if (ERROR_SUCCESS == err) {
      DWORD dwType = 0;
      DWORD data = 0;
      DWORD dwSize = sizeof(DWORD);

      err =
        RegQueryValueExW(hKey, L"~MHz", 0, &dwType, (LPBYTE)&data, &dwSize);

      if (ERROR_SUCCESS == err) {
        this->CPUSpeedInMHz = (float)data;
        retrieved = true;
      }

      RegCloseKey(hKey);
      hKey = NULL;
    }
  }