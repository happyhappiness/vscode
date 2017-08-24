{
  std::vector<std::string> fields;
  if (!LoadLines(fileName, fields)) {
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