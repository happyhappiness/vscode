static int udb_result_prepare_result(udb_result_t const *r, /* {{{ */
                                     udb_result_preparation_area_t *prep_area,
                                     char **column_names, size_t column_num) {
  if ((r == NULL) || (prep_area == NULL))
    return (-EINVAL);

#define BAIL_OUT(status)                                                       \
  prep_area->ds = NULL;                                                        \
  sfree(prep_area->instances_pos);                                             \
  sfree(prep_area->values_pos);                                                \
  sfree(prep_area->metadata_pos);                                              \
  sfree(prep_area->instances_buffer);                                          \
  sfree(prep_area->values_buffer);                                             \
  sfree(prep_area->metadata_buffer);                                           \
  return (status)

  /* Make sure previous preparations are cleaned up. */
  udb_result_finish_result(r, prep_area);
  prep_area->instances_pos = NULL;
  prep_area->values_pos = NULL;
  prep_area->metadata_pos = NULL;

  /* Read `ds' and check number of values {{{ */
  prep_area->ds = plugin_get_ds(r->type);
  if (prep_area->ds == NULL) {
    ERROR("db query utils: udb_result_prepare_result: Type `%s' is not "
          "known by the daemon. See types.db(5) for details.",
          r->type);
    BAIL_OUT(-1);
  }

  if (prep_area->ds->ds_num != r->values_num) {
    ERROR("db query utils: udb_result_prepare_result: The type `%s' "
          "requires exactly %zu value%s, but the configuration specifies %zu.",
          r->type, prep_area->ds->ds_num,
          (prep_area->ds->ds_num == 1) ? "" : "s", r->values_num);
    BAIL_OUT(-1);
  }
  /* }}} */

  /* Allocate r->instances_pos, r->values_pos, r->metadata_post,
   * r->instances_buffer, r->values_buffer, and r->metadata_buffer {{{ */
  if (r->instances_num > 0) {
    prep_area->instances_pos =
        (size_t *)calloc(r->instances_num, sizeof(size_t));
    if (prep_area->instances_pos == NULL) {
      ERROR("db query utils: udb_result_prepare_result: calloc failed.");
      BAIL_OUT(-ENOMEM);
    }

    prep_area->instances_buffer =
        (char **)calloc(r->instances_num, sizeof(char *));
    if (prep_area->instances_buffer == NULL) {
      ERROR("db query utils: udb_result_prepare_result: calloc failed.");
      BAIL_OUT(-ENOMEM);
    }
  } /* if (r->instances_num > 0) */

  prep_area->values_pos = (size_t *)calloc(r->values_num, sizeof(size_t));
  if (prep_area->values_pos == NULL) {
    ERROR("db query utils: udb_result_prepare_result: calloc failed.");
    BAIL_OUT(-ENOMEM);
  }

  prep_area->values_buffer = (char **)calloc(r->values_num, sizeof(char *));
  if (prep_area->values_buffer == NULL) {
    ERROR("db query utils: udb_result_prepare_result: calloc failed.");
    BAIL_OUT(-ENOMEM);
  }

  prep_area->metadata_pos = (size_t *)calloc(r->metadata_num, sizeof(size_t));
  if (prep_area->metadata_pos == NULL) {
    ERROR("db query utils: udb_result_prepare_result: calloc failed.");
    BAIL_OUT(-ENOMEM);
  }

  prep_area->metadata_buffer = (char **)calloc(r->metadata_num, sizeof(char *));
  if (prep_area->metadata_buffer == NULL) {
    ERROR("db query utils: udb_result_prepare_result: calloc failed.");
    BAIL_OUT(-ENOMEM);
  }

  /* }}} */

  /* Determine the position of the plugin instance column {{{ */
  for (size_t i = 0; i < r->instances_num; i++) {
    size_t j;

    for (j = 0; j < column_num; j++) {
      if (strcasecmp(r->instances[i], column_names[j]) == 0) {
        prep_area->instances_pos[i] = j;
        break;
      }
    }

    if (j >= column_num) {
      ERROR("db query utils: udb_result_prepare_result: "
            "Column `%s' could not be found.",
            r->instances[i]);
      BAIL_OUT(-ENOENT);
    }
  } /* }}} for (i = 0; i < r->instances_num; i++) */

  /* Determine the position of the value columns {{{ */
  for (size_t i = 0; i < r->values_num; i++) {
    size_t j;

    for (j = 0; j < column_num; j++) {
      if (strcasecmp(r->values[i], column_names[j]) == 0) {
        prep_area->values_pos[i] = j;
        break;
      }
    }

    if (j >= column_num) {
      ERROR("db query utils: udb_result_prepare_result: "
            "Column `%s' could not be found.",
            r->values[i]);
      BAIL_OUT(-ENOENT);
    }
  } /* }}} for (i = 0; i < r->values_num; i++) */

  /* Determine the position of the metadata columns {{{ */
  for (size_t i = 0; i < r->metadata_num; i++) {
    size_t j;

    for (j = 0; j < column_num; j++) {
      if (strcasecmp(r->metadata[i], column_names[j]) == 0) {
        prep_area->metadata_pos[i] = j;
        break;
      }
    }

    if (j >= column_num) {
      ERROR("db query utils: udb_result_prepare_result: "
            "Metadata column `%s' could not be found.",
            r->values[i]);
      BAIL_OUT(-ENOENT);
    }
  } /* }}} for (i = 0; i < r->metadata_num; i++) */

#undef BAIL_OUT
  return (0);
}