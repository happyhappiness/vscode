static int fhcount_config(const char *key, const char *value) {
  int ret = -1;

  if (strcasecmp(key, "ValuesAbsolute") == 0) {
    if (IS_TRUE(value)) {
      values_absolute = 1;
    } else {
      values_absolute = 0;
    }

    ret = 0;
  } else if (strcasecmp(key, "ValuesPercentage") == 0) {
    if (IS_TRUE(value)) {
      values_percentage = 1;
    } else {
      values_percentage = 0;
    }

    ret = 0;
  }

  return ret;
}