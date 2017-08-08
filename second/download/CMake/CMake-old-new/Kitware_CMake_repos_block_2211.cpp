{
  int res;
  char* nexec = strdup(exec);
  char* fpath = (char*)malloc(strlen(exec) + 100);
  int cc;
  int cnt = 0;
  printf("Process executable name: %s\n", exec);

  // Remove the executable name and directory name
  for (cc = strlen(nexec) - 1; cc > 0; cc--) {
    if (nexec[cc] == '/') {
      nexec[cc] = 0;
      if (cnt == 1) {
        break;
      }
      cnt++;
    }
  }
  printf("Process executable path: %s\n", nexec);
  sprintf(fpath, "%s/%s", nexec, file);
  printf("Check for file: %s\n", fpath);
  res = fileExists(fpath);
  free(nexec);
  free(fpath);
  return res;
}