static ssize_t nss_send(struct connectdata *conn,  /* connection data */
                        int sockindex,             /* socketindex */
                        const void *mem,           /* send this data */
                        size_t len,                /* amount to write */
                        CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  ssize_t rc;

  /* The SelectClientCert() hook uses this for infof() and failf() but the
     handle stored in nss_setup_connect() could have already been freed. */
  BACKEND->data = conn->data;

  rc = PR_Send(BACKEND->handle, mem, (int)len, 0, PR_INTERVAL_NO_WAIT);
  if(rc < 0) {
    PRInt32 err = PR_GetError();
    if(err == PR_WOULD_BLOCK_ERROR)
      *curlcode = CURLE_AGAIN;
    else {
      /* print the error number and error string */
      const char *err_name = nss_error_to_name(err);
      infof(conn->data, "SSL write: error %d (%s)\n", err, err_name);

      /* print a human-readable message describing the error if available */
      nss_print_error_message(conn->data, err);

      *curlcode = (is_cc_error(err))
        ? CURLE_SSL_CERTPROBLEM
        : CURLE_SEND_ERROR;
    }

    return -1;
  }

  return rc; /* number of bytes */
}