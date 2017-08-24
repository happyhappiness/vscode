{
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