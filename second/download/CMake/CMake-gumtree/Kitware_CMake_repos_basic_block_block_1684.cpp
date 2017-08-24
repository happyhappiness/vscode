{
  FILE* file = popen(command, "r");
  if (file == 0) {
    return -1;
  }
  std::vector<std::string> fields;
  int nl = LoadLines(file, fields);
  pclose(file);
  if (nl == 0) {
    return -1;
  }
  int i = 0;
  while (fieldNames[i] != NULL) {
    int ierr = NameValue(fields, fieldNames[i], values[i]);
    if (ierr) {
      return -(i + 2);
    }
    i += 1;
  }
  return 0;
}