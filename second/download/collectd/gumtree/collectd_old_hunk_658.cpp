      ERROR("rrdtool: `CacheTimeout' must "
            "be greater than 0.\n");
      return (1);
    }
    cache_timeout = DOUBLE_TO_CDTIME_T(tmp);
  } else if (strcasecmp("CacheFlush", key) == 0) {
    double tmp = atof(value);
    if (tmp < 0) {
      fprintf(stderr, "rrdtool: `CacheFlush' must "
                      "be greater than 0.\n");
      ERROR("rrdtool: `CacheFlush' must "
            "be greater than 0.\n");
      return (1);
    }
    cache_flush_timeout = DOUBLE_TO_CDTIME_T(tmp);
  } else if (strcasecmp("DataDir", key) == 0) {
    char *tmp;
    size_t len;

    tmp = strdup(value);
    if (tmp == NULL) {
