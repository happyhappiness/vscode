
        vl.interval = strtol(value, &endptr, 0);

        if (endptr == value) {
          fprintf(stderr, "ERROR: Failed to parse interval as number: %s.\n",
                  value);
          return (-1);
        } else if ((endptr != NULL) && (*endptr != '\0')) {
          fprintf(stderr, "WARNING: Ignoring trailing garbage after "
                          "interval: %s.\n",
                  endptr);
        }
      } else {
        fprintf(stderr, "ERROR: putval: Unknown option `%s'.\n", key);
        return (-1);
      }
    } else { /* value list */
      char *value;

      tmp = strchr(argv[i], (int)':');

      if (tmp == NULL) {
        fprintf(stderr, "ERROR: putval: Invalid value list: %s.\n", argv[i]);
        return (-1);
      }

      *tmp = '\0';
      ++tmp;

      if (strcasecmp(argv[i], "N") == 0) {
