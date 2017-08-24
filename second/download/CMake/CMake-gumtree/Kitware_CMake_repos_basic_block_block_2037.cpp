(RegOpenKeyExW(primaryKey, Encoding::ToWide(second).c_str(), 0,
                    SystemToolsMakeRegistryMode(KEY_WRITE, view),
                    &hKey) != ERROR_SUCCESS) {
    return false;
  } else {
    if (RegDeleteValue(hKey, (LPTSTR)valuename.c_str()) == ERROR_SUCCESS) {
      RegCloseKey(hKey);
      return true;
    }
  }