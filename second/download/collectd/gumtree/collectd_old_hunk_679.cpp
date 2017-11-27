
        vl.time = strtol(argv[i], &endptr, 0);

        if (endptr == argv[i]) {
          fprintf(stderr, "ERROR: Failed to parse time as number: %s.\n",
                  argv[i]);
          return (-1);
        } else if ((endptr != NULL) && (*endptr != '\0')) {
          fprintf(stderr, "ERROR: Garbage after time: %s.\n", endptr);
          return (-1);
        }
      }

      values_len = 0;
      value = tmp;
      while (value != NULL) {
