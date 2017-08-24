{
    if(client_cert)
      /* A server might require different authentication based on the
       * particular path being requested by the client.  To support this
       * scenario, we must ensure that a connection will never reuse the
       * authentication data from a previous connection. */
      SSL_InvalidateSession(connssl->handle);

    PR_Close(connssl->handle);
    connssl->handle = NULL;
  }