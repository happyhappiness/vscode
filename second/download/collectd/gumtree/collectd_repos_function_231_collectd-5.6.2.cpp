static int ignore_device_match(ignorelist_t *il, const char *domname,
                               const char *devpath) {
  char *name;
  int n, r;

  if ((domname == NULL) || (devpath == NULL))
    return 0;

  n = sizeof(char) * (strlen(domname) + strlen(devpath) + 2);
  name = malloc(n);
  if (name == NULL) {
    ERROR(PLUGIN_NAME " plugin: malloc failed.");
    return 0;
  }
  ssnprintf(name, n, "%s:%s", domname, devpath);
  r = ignorelist_match(il, name);
  sfree(name);
  return r;
}