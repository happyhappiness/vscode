static int c_psql_begin(c_psql_database_t *db) {
  PGresult *r = PQexec(db->conn, "BEGIN");

  int status = 1;

  if (r != NULL) {
    if (PGRES_COMMAND_OK == PQresultStatus(r)) {
      db->next_commit = cdtime() + db->commit_interval;
      status = 0;
    } else
      log_warn("Failed to initiate ('BEGIN') transaction: %s",
               PQerrorMessage(db->conn));
    PQclear(r);
  }
  return status;
}