(RegQueryValueExW(processor_key,
                         L"~MHz",
                         NULL,
                         NULL,
                         (BYTE*) &cpu_speed,
                         &cpu_speed_size) != ERROR_SUCCESS) {
      err = GetLastError();
      RegCloseKey(processor_key);
      goto error;
    }