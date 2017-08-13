{
    WCHAR key_name[128];
    HKEY processor_key;
    DWORD cpu_speed;
    DWORD cpu_speed_size = sizeof(cpu_speed);
    WCHAR cpu_brand[256];
    DWORD cpu_brand_size = sizeof(cpu_brand);
    size_t len;

    len = _snwprintf(key_name,
                     ARRAY_SIZE(key_name),
                     L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\%d",
                     i);

    assert(len > 0 && len < ARRAY_SIZE(key_name));

    r = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      key_name,
                      0,
                      KEY_QUERY_VALUE,
                      &processor_key);
    if (r != ERROR_SUCCESS) {
      err = GetLastError();
      goto error;
    }

    if (RegQueryValueExW(processor_key,
                         L"~MHz",
                         NULL,
                         NULL,
                         (BYTE*) &cpu_speed,
                         &cpu_speed_size) != ERROR_SUCCESS) {
      err = GetLastError();
      RegCloseKey(processor_key);
      goto error;
    }

    if (RegQueryValueExW(processor_key,
                         L"ProcessorNameString",
                         NULL,
                         NULL,
                         (BYTE*) &cpu_brand,
                         &cpu_brand_size) != ERROR_SUCCESS) {
      err = GetLastError();
      RegCloseKey(processor_key);
      goto error;
    }

    RegCloseKey(processor_key);

    cpu_info = &cpu_infos[i];
    cpu_info->speed = cpu_speed;
    cpu_info->cpu_times.user = sppi[i].UserTime.QuadPart / 10000;
    cpu_info->cpu_times.sys = (sppi[i].KernelTime.QuadPart -
        sppi[i].IdleTime.QuadPart) / 10000;
    cpu_info->cpu_times.idle = sppi[i].IdleTime.QuadPart / 10000;
    cpu_info->cpu_times.irq = sppi[i].InterruptTime.QuadPart / 10000;
    cpu_info->cpu_times.nice = 0;

    uv__convert_utf16_to_utf8(cpu_brand,
                              cpu_brand_size / sizeof(WCHAR),
                              &(cpu_info->model));
  }