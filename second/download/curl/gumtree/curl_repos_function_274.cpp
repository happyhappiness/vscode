void Curl_ossl_close(struct connectdata *conn)
{
  int i;
  /*
    ERR_remove_state() frees the error queue associated with
    thread pid.  If pid == 0, the current thread will have its
    error queue removed.

    Since error queue data structures are allocated
    automatically for new threads, they must be freed when
    threads are terminated in oder to avoid memory leaks.
  */
  ERR_remove_state(0);

  for(i=0; i<2; i++) {
    struct ssl_connect_data *connssl = &conn->ssl[i];

    if(connssl->handle) {
      (void)SSL_shutdown(connssl->handle);
      SSL_set_connect_state(connssl->handle);

      SSL_free (connssl->handle);
      connssl->handle = NULL;
    }
    if(connssl->ctx) {
      SSL_CTX_free (connssl->ctx);
      connssl->ctx = NULL;
    }
    connssl->use = FALSE; /* get back to ordinary socket usage */
  }
}