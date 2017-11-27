static int c_psql_shutdown(void) {
  _Bool had_flush = 0;

  plugin_unregister_read_group("postgresql");

  for (size_t i = 0; i < databases_num; ++i) {
    c_psql_database_t *db = databases[i];

    if (db->writers_num > 0) {
      char cb_name[DATA_MAX_NAME_LEN];
      snprintf(cb_name, sizeof(cb_name), "postgresql-%s", db->database);

      if (!had_flush) {
        plugin_unregister_flush("postgresql");
        had_flush = 1;
      }

      plugin_unregister_flush(cb_name);
      plugin_unregister_write(cb_name);
    }

    sfree(db);
  }

  udb_query_free(queries, queries_num);
  queries = NULL;
  queries_num = 0;

  sfree(writers);
  writers = NULL;
  writers_num = 0;

  sfree(databases);
  databases = NULL;
  databases_num = 0;

  return 0;
}