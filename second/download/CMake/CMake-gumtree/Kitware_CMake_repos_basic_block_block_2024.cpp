{
  HKEY primaryKey = HKEY_CURRENT_USER;
  std::string second;
  std::string valuename;
  if (!SystemToolsParseRegistryKey(key, primaryKey, second, valuename)) {
    return false;
  }

  HKEY hKey;
  if (RegOpenKeyExW(primaryKey, Encoding::ToWide(second).c_str(), 0,
                    SystemToolsMakeRegistryMode(KEY_READ, view),
                    &hKey) != ERROR_SUCCESS) {
    return false;
  } else {
    wchar_t name[1024];
    DWORD dwNameSize = sizeof(name) / sizeof(name[0]);

    DWORD i = 0;
    while (RegEnumKeyW(hKey, i, name, dwNameSize) == ERROR_SUCCESS) {
      subkeys.push_back(Encoding::ToNarrow(name));
      ++i;
    }

    RegCloseKey(hKey);
  }

  return true;
}