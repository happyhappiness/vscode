static int c_psql_exec_query(c_psql_database_t *db, udb_query_t *q,
                             udb_query_preparation_area_t *prep_area) {
  PGresult *res;

  c_psql_user_data_t *data;

  const char *host;

  char **column_names;
  char **column_values;
  int column_num;

  int rows_num;
  int status;

  /* The user data may hold parameter information, but may be NULL. */
  data = udb_query_get_user_data(q);

  /* Versions up to `3' don't know how to handle parameters. */
  if (3 <= db->proto_version)
    res = c_psql_exec_query_params(db, q, data);
  else if ((NULL == data) || (0 == data->params_num))
    res = c_psql_exec_query_noparams(db, q);
  else {
    log_err("Connection to database \"%s\" (%s) does not support "
            "parameters (protocol version %d) - "
            "cannot execute query \"%s\".",
            db->database, db->instance, db->proto_version,
            udb_query_get_name(q));
    return -1;
  }

  /* give c_psql_write() a chance to acquire the lock if called recursively
   * through dispatch_values(); this will happen if, both, queries and
   * writers are configured for a single connection */
  pthread_mutex_unlock(&db->db_lock);

  column_names = NULL;
  column_values = NULL;

  if (PGRES_TUPLES_OK != PQresultStatus(res)) {
    pthread_mutex_lock(&db->db_lock);

    if ((CONNECTION_OK != PQstatus(db->conn)) &&
        (0 == c_psql_check_connection(db))) {
      PQclear(res);
      return c_psql_exec_query(db, q, prep_area);
    }

    log_err("Failed to execute SQL query: %s", PQerrorMessage(db->conn));
    log_info("SQL query was: %s", udb_query_get_statement(q));
    PQclear(res);
    return -1;
  }

#define BAIL_OUT(status)                                                       \
  sfree(column_names);                                                         \
  sfree(column_values);                                                        \
  PQclear(res);                                                                \
  pthread_mutex_lock(&db->db_lock);                                            \
  return status

  rows_num = PQntuples(res);
  if (1 > rows_num) {
    BAIL_OUT(0);
  }

  column_num = PQnfields(res);
  column_names = (char **)calloc(column_num, sizeof(char *));
  if (NULL == column_names) {
    log_err("calloc failed.");
    BAIL_OUT(-1);
  }

  column_values = (char **)calloc(column_num, sizeof(char *));
  if (NULL == column_values) {
    log_err("calloc failed.");
    BAIL_OUT(-1);
  }

  for (int col = 0; col < column_num; ++col) {
    /* Pointers returned by `PQfname' are freed by `PQclear' via
     * `BAIL_OUT'. */
    column_names[col] = PQfname(res, col);
    if (NULL == column_names[col]) {
      log_err("Failed to resolve name of column %i.", col);
      BAIL_OUT(-1);
    }
  }

  if (C_PSQL_IS_UNIX_DOMAIN_SOCKET(db->host) ||
      (0 == strcmp(db->host, "127.0.0.1")) ||
      (0 == strcmp(db->host, "localhost")))
    host = hostname_g;
  else
    host = db->host;

  status = udb_query_prepare_result(
      q, prep_area, host,
      (db->plugin_name != NULL) ? db->plugin_name : "postgresql", db->instance,
      column_names, (size_t)column_num, db->interval);

  if (0 != status) {
    log_err("udb_query_prepare_result failed with status %i.", status);
    BAIL_OUT(-1);
  }

  for (int row = 0; row < rows_num; ++row) {
    int col;
    for (col = 0; col < column_num; ++col) {
      /* Pointers returned by `PQgetvalue' are freed by `PQclear' via
       * `BAIL_OUT'. */
      column_values[col] = PQgetvalue(res, row, col);
      if (NULL == column_values[col]) {
        log_err("Failed to get value at (row = %i, col = %i).", row, col);
        break;
      }
    }

    /* check for an error */
    if (col < column_num)
      continue;

    status = udb_query_handle_result(q, prep_area, column_values);
    if (status != 0) {
      log_err("udb_query_handle_result failed with status %i.", status);
    }
  } /* for (row = 0; row < rows_num; ++row) */

  udb_query_finish_result(q, prep_area);

  BAIL_OUT(0);
#undef BAIL_OUT
}