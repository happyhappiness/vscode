static void c_psql_database_delete(void *data) {
  c_psql_database_t *db = data;

  --db->ref_cnt;
  /* readers and writers may access this database */
  if (db->ref_cnt > 0)
    return;

  /* wait for the lock to be released by the last writer */
  pthread_mutex_lock(&db->db_lock);

  if (db->next_commit > 0)
    c_psql_commit(db);

  PQfinish(db->conn);
  db->conn = NULL;

  if (db->q_prep_areas)
    for (size_t i = 0; i < db->queries_num; ++i)
      udb_query_delete_preparation_area(db->q_prep_areas[i]);
  free(db->q_prep_areas);

  sfree(db->queries);
  db->queries_num = 0;

  sfree(db->writers);
  db->writers_num = 0;

  pthread_mutex_unlock(&db->db_lock);

  pthread_mutex_destroy(&db->db_lock);

  sfree(db->database);
  sfree(db->host);
  sfree(db->port);
  sfree(db->user);
  sfree(db->password);

  sfree(db->instance);

  sfree(db->plugin_name);

  sfree(db->sslmode);

  sfree(db->krbsrvname);

  sfree(db->service);

  /* don't care about freeing or reordering the 'databases' array
   * this is done in 'shutdown'; also, don't free the database instance
   * object just to make sure that in case anybody accesses it before
   * shutdown won't segfault */
  return;
}