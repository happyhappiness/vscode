static int uuid_config(const char *key, const char *value) {
  if (strcasecmp(key, "UUIDFile") == 0) {
    char *tmp = strdup(value);
    if (tmp == NULL)
      return -1;
    sfree(uuidfile);
    uuidfile = tmp;
    return 0;
  }

  return 1;
}