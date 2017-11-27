  char *ret;

  strsize = strlen(str) + 1;
  ret = (char *)malloc(strsize);
  if (ret != NULL)
    memcpy(ret, str, strsize);
  return ret;
} /* }}} char *cn_strdup */

static int filter_ds(size_t *values_num, double **values,
                     char ***values_names) {
  gauge_t *new_values;
  char **new_names;

  if (match_ds_g == NULL)
    return RET_OKAY;

  new_values = (gauge_t *)calloc(match_ds_num_g, sizeof(*new_values));
  if (new_values == NULL) {
    fprintf(stderr, "calloc failed: %s\n", strerror(errno));
    return RET_UNKNOWN;
  }

  new_names = (char **)calloc(match_ds_num_g, sizeof(*new_names));
  if (new_names == NULL) {
    fprintf(stderr, "calloc failed: %s\n", strerror(errno));
    free(new_values);
    return RET_UNKNOWN;
  }

  for (size_t i = 0; i < match_ds_num_g; i++) {
    size_t j;

    /* match_ds_g keeps pointers into argv but the names will be freed */
