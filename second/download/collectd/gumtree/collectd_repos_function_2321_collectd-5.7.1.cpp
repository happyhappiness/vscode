static int conntrack_config(const char *key, const char *value) {
  if (strcmp(key, "OldFiles") == 0)
    old_files = 1;

  return 0;
}