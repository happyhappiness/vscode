static PGresult *c_psql_exec_query_noparams(c_psql_database_t *db,
                                            udb_query_t *q) {
  return PQexec(db->conn, udb_query_get_statement(q));
}