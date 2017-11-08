void Curl_SSL_Close(struct connectdata *conn)
{
  if (conn->ssl.use) {
    /*
      ERR_remove_state() frees the error queue associated with
      thread pid.  If pid == 0, the current thread will have its
      error queue removed.

      Since error queue data structures are allocated
      automatically for new threads, they must be freed when
      threads are terminated in oder to avoid memory leaks.
    */
    ERR_remove_state(0);

    if(conn->ssl.handle) {
      (void)SSL_shutdown(conn->ssl.handle);
      SSL_set_connect_state(conn->ssl.handle);

      SSL_free (conn->ssl.handle);
      conn->ssl.handle = NULL;
    }
    if(conn->ssl.ctx) {
      SSL_CTX_free (conn->ssl.ctx);
      conn->ssl.ctx = NULL;
    }
    conn->ssl.use = FALSE; /* get back to ordinary socket usage */
  }
}