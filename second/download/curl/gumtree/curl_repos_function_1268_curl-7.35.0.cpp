static CURLcode ConnectionStore(struct SessionHandle *data,
                                struct connectdata *conn)
{
  static int connection_id_counter = 0;

  CURLcode result;

  /* Assign a number to the connection for easier tracking in the log
     output */
  conn->connection_id = connection_id_counter++;

  result = Curl_conncache_add_conn(data->state.conn_cache, conn);
  if(result != CURLE_OK)
    conn->connection_id = -1;

  return result;
}