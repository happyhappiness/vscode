static ssize_t nss_recv(struct connectdata *conn,  /* connection data */
                        int sockindex,             /* socketindex */
                        char *buf,                 /* store read data here */
                        size_t buffersize,         /* max amount to read */
                        CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  ssize_t nread;

  /* The SelectClientCert() hook uses this for infof() and failf() but the
     handle stored in nss_setup_connect() could have already been freed. */
  BACKEND->data = conn->data;

  nread = PR_Recv(BACKEND->handle, buf, (int)buffersize, 0,
                  PR_INTERVAL_NO_WAIT);
  if(nread < 0) {
    /* failed SSL read */
    PRInt32 err = PR_GetError();

    if(err == PR_WOULD_BLOCK_ERROR)
      *curlcode = CURLE_AGAIN;
    else {
      /* print the error number and error string */
      const char *err_name = nss_error_to_name(err);
      infof(conn->data, "SSL read: errno %d (%s)\n", err, err_name);

      /* print a human-readable message describing the error if available */
      nss_print_error_message(conn->data, err);

      *curlcode = (is_cc_error(err))
        ? CURLE_SSL_CERTPROBLEM
        : CURLE_RECV_ERROR;
    }

    return -1;
  }

  return nread;
}