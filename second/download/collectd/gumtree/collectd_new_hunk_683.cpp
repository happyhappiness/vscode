    if (new_names[i] == NULL) {
      fprintf(stderr, "cn_strdup failed: %s\n", strerror(errno));
      free(new_values);
      for (j = 0; j < i; j++)
        free(new_names[j]);
      free(new_names);
      return RET_UNKNOWN;
    }

    for (j = 0; j < *values_num; j++)
      if (strcasecmp(new_names[i], (*values_names)[j]) == 0)
        break;

    if (j == *values_num) {
      printf("ERROR: DS `%s' is not available.\n", new_names[i]);
      free(new_values);
      for (j = 0; j <= i; j++)
        free(new_names[j]);
      free(new_names);
      return RET_CRITICAL;
    }

    new_values[i] = (*values)[j];
  }

  free(*values);
