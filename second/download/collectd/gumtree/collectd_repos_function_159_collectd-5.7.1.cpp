static int cdbi_read_database_query(cdbi_database_t *db, /* {{{ */
                                    udb_query_t *q,
                                    udb_query_preparation_area_t *prep_area) {
  const char *statement;
  dbi_result res;
  size_t column_num;
  char **column_names;
  char **column_values;
  int status;

/* Macro that cleans up dynamically allocated memory and returns the
 * specified status. */
#define BAIL_OUT(status)                                                       \
  if (column_names != NULL) {                                                  \
    sfree(column_names[0]);                                                    \
    sfree(column_names);                                                       \
  }                                                                            \
  if (column_values != NULL) {                                                 \
    sfree(column_values[0]);                                                   \
    sfree(column_values);                                                      \
  }                                                                            \
  if (res != NULL) {                                                           \
    dbi_result_free(res);                                                      \
    res = NULL;                                                                \
  }                                                                            \
  return (status)

  column_names = NULL;
  column_values = NULL;

  statement = udb_query_get_statement(q);
  assert(statement != NULL);

  res = dbi_conn_query(db->connection, statement);
  if (res == NULL) {
    char errbuf[1024];
    ERROR("dbi plugin: cdbi_read_database_query (%s, %s): "
          "dbi_conn_query failed: %s",
          db->name, udb_query_get_name(q),
          cdbi_strerror(db->connection, errbuf, sizeof(errbuf)));
    BAIL_OUT(-1);
  } else /* Get the number of columns */
  {
    unsigned int db_status;

    db_status = dbi_result_get_numfields(res);
    if (db_status == DBI_FIELD_ERROR) {
      char errbuf[1024];
      ERROR("dbi plugin: cdbi_read_database_query (%s, %s): "
            "dbi_result_get_numfields failed: %s",
            db->name, udb_query_get_name(q),
            cdbi_strerror(db->connection, errbuf, sizeof(errbuf)));
      BAIL_OUT(-1);
    }

    column_num = (size_t)db_status;
    DEBUG("cdbi_read_database_query (%s, %s): There are %zu columns.", db->name,
          udb_query_get_name(q), column_num);
  }

  /* Allocate `column_names' and `column_values'. {{{ */
  column_names = calloc(column_num, sizeof(*column_names));
  if (column_names == NULL) {
    ERROR("dbi plugin: calloc failed.");
    BAIL_OUT(-1);
  }

  column_names[0] = calloc(column_num, DATA_MAX_NAME_LEN);
  if (column_names[0] == NULL) {
    ERROR("dbi plugin: calloc failed.");
    BAIL_OUT(-1);
  }
  for (size_t i = 1; i < column_num; i++)
    column_names[i] = column_names[i - 1] + DATA_MAX_NAME_LEN;

  column_values = calloc(column_num, sizeof(*column_values));
  if (column_values == NULL) {
    ERROR("dbi plugin: calloc failed.");
    BAIL_OUT(-1);
  }

  column_values[0] = calloc(column_num, DATA_MAX_NAME_LEN);
  if (column_values[0] == NULL) {
    ERROR("dbi plugin: calloc failed.");
    BAIL_OUT(-1);
  }
  for (size_t i = 1; i < column_num; i++)
    column_values[i] = column_values[i - 1] + DATA_MAX_NAME_LEN;
  /* }}} */

  /* Copy the field names to `column_names' */
  for (size_t i = 0; i < column_num; i++) /* {{{ */
  {
    const char *column_name;

    column_name = dbi_result_get_field_name(res, (unsigned int)(i + 1));
    if (column_name == NULL) {
      ERROR("dbi plugin: cdbi_read_database_query (%s, %s): "
            "Cannot retrieve name of field %zu.",
            db->name, udb_query_get_name(q), i + 1);
      BAIL_OUT(-1);
    }

    sstrncpy(column_names[i], column_name, DATA_MAX_NAME_LEN);
  } /* }}} for (i = 0; i < column_num; i++) */

  udb_query_prepare_result(
      q, prep_area, (db->host ? db->host : hostname_g),
      /* plugin = */ "dbi", db->name, column_names, column_num,
      /* interval = */ (db->interval > 0) ? db->interval : 0);

  /* 0 = error; 1 = success; */
  status = dbi_result_first_row(res); /* {{{ */
  if (status != 1) {
    char errbuf[1024];
    ERROR("dbi plugin: cdbi_read_database_query (%s, %s): "
          "dbi_result_first_row failed: %s. Maybe the statement didn't "
          "return any rows?",
          db->name, udb_query_get_name(q),
          cdbi_strerror(db->connection, errbuf, sizeof(errbuf)));
    udb_query_finish_result(q, prep_area);
    BAIL_OUT(-1);
  } /* }}} */

  /* Iterate over all rows and call `udb_query_handle_result' with each list of
   * values. */
  while (42) /* {{{ */
  {
    status = 0;
    /* Copy the value of the columns to `column_values' */
    for (size_t i = 0; i < column_num; i++) /* {{{ */
    {
      status = cdbi_result_get_field(res, (unsigned int)(i + 1),
                                     column_values[i], DATA_MAX_NAME_LEN);

      if (status != 0) {
        ERROR("dbi plugin: cdbi_read_database_query (%s, %s): "
              "cdbi_result_get_field (%zu) failed.",
              db->name, udb_query_get_name(q), i + 1);
        status = -1;
        break;
      }
    } /* }}} for (i = 0; i < column_num; i++) */

    /* If all values were copied successfully, call `udb_query_handle_result'
     * to dispatch the row to the daemon. */
    if (status == 0) /* {{{ */
    {
      status = udb_query_handle_result(q, prep_area, column_values);
      if (status != 0) {
        ERROR("dbi plugin: cdbi_read_database_query (%s, %s): "
              "udb_query_handle_result failed.",
              db->name, udb_query_get_name(q));
      }
    } /* }}} */

    /* Get the next row from the database. */
    status = dbi_result_next_row(res); /* {{{ */
    if (status != 1) {
      if (dbi_conn_error(db->connection, NULL) != 0) {
        char errbuf[1024];
        WARNING("dbi plugin: cdbi_read_database_query (%s, %s): "
                "dbi_result_next_row failed: %s.",
                db->name, udb_query_get_name(q),
                cdbi_strerror(db->connection, errbuf, sizeof(errbuf)));
      }
      break;
    } /* }}} */
  }   /* }}} while (42) */

  /* Tell the db query interface that we're done with this query. */
  udb_query_finish_result(q, prep_area);

  /* Clean up and return `status = 0' (success) */
  BAIL_OUT(0);
#undef BAIL_OUT
}