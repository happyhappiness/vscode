static int rrd_config(const char *key, const char *value) {
  if (strcasecmp("CacheTimeout", key) == 0) {
    double tmp = atof(value);
    if (tmp < 0) {
      fprintf(stderr, "rrdtool: `CacheTimeout' must "
                      "be greater than 0.\n");
      ERROR("rrdtool: `CacheTimeout' must "
            "be greater than 0.\n");
      return 1;
    }
    cache_timeout = DOUBLE_TO_CDTIME_T(tmp);
  } else if (strcasecmp("CacheFlush", key) == 0) {
    double tmp = atof(value);
    if (tmp < 0) {
      fprintf(stderr, "rrdtool: `CacheFlush' must "
                      "be greater than 0.\n");
      ERROR("rrdtool: `CacheFlush' must "
            "be greater than 0.\n");
      return 1;
    }
    cache_flush_timeout = DOUBLE_TO_CDTIME_T(tmp);
  } else if (strcasecmp("DataDir", key) == 0) {
    char *tmp;
    size_t len;

    tmp = strdup(value);
    if (tmp == NULL) {
      ERROR("rrdtool plugin: strdup failed.");
      return 1;
    }

    len = strlen(tmp);
    while ((len > 0) && (tmp[len - 1] == '/')) {
      len--;
      tmp[len] = 0;
    }

    if (len == 0) {
      ERROR("rrdtool plugin: Invalid \"DataDir\" option.");
      sfree(tmp);
      return 1;
    }

    if (datadir != NULL) {
      sfree(datadir);
    }

    datadir = tmp;
  } else if (strcasecmp("StepSize", key) == 0) {
    unsigned long temp = strtoul(value, NULL, 0);
    if (temp > 0)
      rrdcreate_config.stepsize = temp;
  } else if (strcasecmp("HeartBeat", key) == 0) {
    int temp = atoi(value);
    if (temp > 0)
      rrdcreate_config.heartbeat = temp;
  } else if (strcasecmp("CreateFilesAsync", key) == 0) {
    if (IS_TRUE(value))
      rrdcreate_config.async = 1;
    else
      rrdcreate_config.async = 0;
  } else if (strcasecmp("RRARows", key) == 0) {
    int tmp = atoi(value);
    if (tmp <= 0) {
      fprintf(stderr, "rrdtool: `RRARows' must "
                      "be greater than 0.\n");
      ERROR("rrdtool: `RRARows' must "
            "be greater than 0.\n");
      return 1;
    }
    rrdcreate_config.rrarows = tmp;
  } else if (strcasecmp("RRATimespan", key) == 0) {
    char *saveptr = NULL;
    char *dummy;
    char *ptr;
    char *value_copy;
    int *tmp_alloc;

    value_copy = strdup(value);
    if (value_copy == NULL)
      return 1;

    dummy = value_copy;
    while ((ptr = strtok_r(dummy, ", \t", &saveptr)) != NULL) {
      dummy = NULL;

      tmp_alloc = realloc(rrdcreate_config.timespans,
                          sizeof(int) * (rrdcreate_config.timespans_num + 1));
      if (tmp_alloc == NULL) {
        fprintf(stderr, "rrdtool: realloc failed.\n");
        ERROR("rrdtool: realloc failed.\n");
        free(value_copy);
        return 1;
      }
      rrdcreate_config.timespans = tmp_alloc;
      rrdcreate_config.timespans[rrdcreate_config.timespans_num] = atoi(ptr);
      if (rrdcreate_config.timespans[rrdcreate_config.timespans_num] != 0)
        rrdcreate_config.timespans_num++;
    } /* while (strtok_r) */

    qsort(/* base = */ rrdcreate_config.timespans,
          /* nmemb  = */ rrdcreate_config.timespans_num,
          /* size   = */ sizeof(rrdcreate_config.timespans[0]),
          /* compar = */ rrd_compare_numeric);

    free(value_copy);
  } else if (strcasecmp("XFF", key) == 0) {
    double tmp = atof(value);
    if ((tmp < 0.0) || (tmp >= 1.0)) {
      fprintf(stderr, "rrdtool: `XFF' must "
                      "be in the range 0 to 1 (exclusive).");
      ERROR("rrdtool: `XFF' must "
            "be in the range 0 to 1 (exclusive).");
      return 1;
    }
    rrdcreate_config.xff = tmp;
  } else if (strcasecmp("WritesPerSecond", key) == 0) {
    double wps = atof(value);

    if (wps < 0.0) {
      fprintf(stderr, "rrdtool: `WritesPerSecond' must be "
                      "greater than or equal to zero.");
      return 1;
    } else if (wps == 0.0) {
      write_rate = 0.0;
    } else {
      write_rate = 1.0 / wps;
    }
  } else if (strcasecmp("RandomTimeout", key) == 0) {
    double tmp;

    tmp = atof(value);
    if (tmp < 0.0) {
      fprintf(stderr, "rrdtool: `RandomTimeout' must "
                      "be greater than or equal to zero.\n");
      ERROR("rrdtool: `RandomTimeout' must "
            "be greater then or equal to zero.");
    } else {
      random_timeout = DOUBLE_TO_CDTIME_T(tmp);
    }
  } else {
    return -1;
  }
  return 0;
}