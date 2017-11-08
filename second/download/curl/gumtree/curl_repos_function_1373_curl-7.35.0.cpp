static void close_all_connections(struct Curl_multi *multi)
{
  struct connectdata *conn;

  conn = Curl_conncache_find_first_connection(multi->conn_cache);
  while(conn) {
    conn->data = multi->closure_handle;

    /* This will remove the connection from the cache */
    (void)Curl_disconnect(conn, FALSE);

    conn = Curl_conncache_find_first_connection(multi->conn_cache);
  }
}