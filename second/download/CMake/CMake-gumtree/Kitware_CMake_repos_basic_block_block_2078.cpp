{
  if (!str1) {
    return SystemTools::AppendStrings(str2, str3);
  }
  if (!str2) {
    return SystemTools::AppendStrings(str1, str3);
  }
  if (!str3) {
    return SystemTools::AppendStrings(str1, str2);
  }

  size_t len1 = strlen(str1), len2 = strlen(str2);
  char* newstr = new char[len1 + len2 + strlen(str3) + 1];
  if (!newstr) {
    return 0;
  }
  strcpy(newstr, str1);
  strcat(newstr + len1, str2);
  strcat(newstr + len1 + len2, str3);
  return newstr;
}