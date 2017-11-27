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
