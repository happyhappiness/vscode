{
  std::wstring wEnv = Encoding::ToWide(env);
  size_t const pos = wEnv.find('=');
  size_t const len = pos == std::string::npos ? wEnv.size() : pos;
  wEnv.resize(len + 1, L'=');
  wchar_t* newEnv = _wcsdup(wEnv.c_str());
  if (!newEnv) {
    return -1;
  }
  kwsysEnvSet::Free oldEnv(kwsysUnPutEnvSet.Release(newEnv));
  kwsysUnPutEnvSet.insert(newEnv);
  return _wputenv(newEnv);
}