static MYSQL_RES *exec_query(MYSQL *con, const char *query) {
  MYSQL_RES *res;

  int query_len = strlen(query);

  if (mysql_real_query(con, query, query_len)) {
    ERROR("mysql plugin: Failed to execute query: %s", mysql_error(con));
    INFO("mysql plugin: SQL query was: %s", query);
    return (NULL);
  }

  res = mysql_store_result(con);
  if (res == NULL) {
    ERROR("mysql plugin: Failed to store query result: %s", mysql_error(con));
    INFO("mysql plugin: SQL query was: %s", query);
    return (NULL);
  }

  return (res);
}