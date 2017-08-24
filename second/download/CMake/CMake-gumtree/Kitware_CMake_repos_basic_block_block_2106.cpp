{
  if (str) {
    char* newstr = new char[strlen(str) + 1];
    return strcpy(newstr, str);
  }
  return NULL;
}