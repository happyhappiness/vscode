{
  int line, column;
  getLocationLineAndColumn(location, line, column);
  char buffer[18 + 16 + 16 + 1];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__)
#if defined(WINCE)
  _snprintf(buffer, sizeof(buffer), "Line %d, Column %d", line, column);
#else
  sprintf_s(buffer, sizeof(buffer), "Line %d, Column %d", line, column);
#endif
#else
  snprintf(buffer, sizeof(buffer), "Line %d, Column %d", line, column);
#endif
  return buffer;
}