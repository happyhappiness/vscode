static int cdbi_read_database (cdbi_database_t *db) /* {{{ */
{
  size_t i;
  int success;
  int status;

  unsigned int db_version;

  status = cdbi_connect_database (db);
  if (status != 0)
    return (status);
  assert (db->connection != NULL);

  db_version = dbi_conn_get_engine_version (db->connection);
  /* TODO: Complain if `db_version == 0' */

  success = 0;
  for (i = 0; i < db->queries_num; i++)
  {
    /* Check if we know the database's version and if so, if this query applies
     * to that version. */
    if ((db_version != 0)
        && (udb_query_check_version (db->queries[i], db_version) == 0))
      continue;

    status = cdbi_read_database_query (db,
        db->queries[i], db->q_prep_areas[i]);
    if (status == 0)
      success++;
  }

  if (success == 0)
  {
    ERROR ("dbi plugin: All queries failed for database `%s'.", db->name);
    return (-1);
  }

  return (0);
}