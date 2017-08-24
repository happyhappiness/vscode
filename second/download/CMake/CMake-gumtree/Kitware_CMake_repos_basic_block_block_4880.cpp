{
    SIGPIPE_VARIABLE(pipe_st);
    conn->data = multi->closure_handle;

    sigpipe_ignore(conn->data, &pipe_st);
    conn->data->easy_conn = NULL; /* clear the easy handle's connection
                                     pointer */
    /* This will remove the connection from the cache */
    connclose(conn, "kill all");
    (void)Curl_disconnect(conn, FALSE);
    sigpipe_restore(&pipe_st);

    conn = Curl_conncache_find_first_connection(&multi->conn_cache);
  }