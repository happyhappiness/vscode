{
    DEBUGASSERT(ssl_connection_complete == conn->proxy_ssl[sockindex].state);
    DEBUGASSERT(conn->proxy_ssl[sockindex].handle != NULL);
    nspr_io = conn->proxy_ssl[sockindex].handle;
    second_layer = TRUE;
  }