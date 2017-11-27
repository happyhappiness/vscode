static int csv_config(const char *key, const char *value) {
  if (strcasecmp("DataDir", key) == 0) {
    if (datadir != NULL) {
      free(datadir);
      datadir = NULL;
    }
    if (strcasecmp("stdout", value) == 0) {
      use_stdio = 1;
      return (0);
    } else if (strcasecmp("stderr", value) == 0) {
      use_stdio = 2;
      return (0);
    }
    datadir = strdup(value);
    if (datadir != NULL) {
      int len = strlen(datadir);
      while ((len > 0) && (datadir[len - 1] == '/')) {
        len--;
        datadir[len] = '\0';
      }
      if (len <= 0) {
        free(datadir);
        datadir = NULL;
      }
    }
  } else if (strcasecmp("StoreRates", key) == 0) {
    if (IS_TRUE(value))
      store_rates = 1;
    else
      store_rates = 0;
  } else {
    return (-1);
  }
  return (0);
}