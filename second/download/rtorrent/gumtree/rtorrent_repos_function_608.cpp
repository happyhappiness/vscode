inline TextElementStringBase*
te_string(const char* str) {
  return new TextElementCString(str);
}