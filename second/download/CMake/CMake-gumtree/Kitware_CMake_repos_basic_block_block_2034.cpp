{
  HKEY primaryKey = HKEY_CURRENT_USER;
  std::string second;
  std::string valuename;
  if (!SystemToolsParseRegistryKey(key, primaryKey, second, valuename)) {
    return false;
  }

  HKEY hKey;
  DWORD dwDummy;
  wchar_t lpClass[] = L"";
  if (RegCreateKeyExW(primaryKey, Encoding::ToWide(second).c_str(), 0, lpClass,
                      REG_OPTION_NON_VOLATILE,
                      SystemToolsMakeRegistryMode(KEY_WRITE, view), NULL,
                      &hKey, &dwDummy) != ERROR_SUCCESS) {
    return false;
  }

  std::wstring wvalue = Encoding::ToWide(value);
  if (RegSetValueExW(hKey, Encoding::ToWide(valuename).c_str(), 0, REG_SZ,
                     (CONST BYTE*)wvalue.c_str(),
                     (DWORD)(sizeof(wchar_t) * (wvalue.size() + 1))) ==
      ERROR_SUCCESS) {
    return true;
  }
  return false;
}