{
  // do while hangs if replaceSize is 0
  if (!*replace) {
    return;
  }

  SystemTools::ReplaceString(source, replace, strlen(replace),
                             with ? with : "");
}