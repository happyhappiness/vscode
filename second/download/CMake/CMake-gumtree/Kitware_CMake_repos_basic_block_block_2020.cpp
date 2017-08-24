{
  // only add the modes when on a system that supports Wow64.
  static FARPROC wow64p =
    GetProcAddress(GetModuleHandleW(L"kernel32"), "IsWow64Process");
  if (wow64p == NULL) {
    return mode;
  }

  if (view == SystemTools::KeyWOW64_32) {
    return mode | KWSYS_ST_KEY_WOW64_32KEY;
  } else if (view == SystemTools::KeyWOW64_64) {
    return mode | KWSYS_ST_KEY_WOW64_64KEY;
  }
  return mode;
}