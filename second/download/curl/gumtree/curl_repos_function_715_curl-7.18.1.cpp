static CURLcode setup_connection_internals(struct SessionHandle *data,
                                           struct connectdata *conn)
{
  const struct Curl_handler * const * pp;
  const struct Curl_handler * p;
  CURLcode result;

  conn->socktype = SOCK_STREAM; /* most of them are TCP streams */

  /* Scan protocol handler table. */

  for (pp = protocols; (p = *pp) != NULL; pp++)
    if(strequal(p->scheme, conn->protostr)) {
      /* Protocol found in table. Perform setup complement if some. */
      conn->handler = p;

      if(p->setup_connection) {
        result = (*p->setup_connection)(conn);

        if(result != CURLE_OK)
          return result;

        p = conn->handler;              /* May have changed. */
      }

      conn->port = p->defport;
      conn->remote_port = (unsigned short)p->defport;
      conn->protocol |= p->protocol;
      return CURLE_OK;
    }

  /* The protocol was not found in the table, but we don't have to assign it
     to anything since it is already assigned to a dummy-struct in the
     CreateConnection() function when the connectdata struct is allocated. */
  failf(data, "Protocol %s not supported or disabled in " LIBCURL_NAME,
        conn->protostr);
  return CURLE_UNSUPPORTED_PROTOCOL;
}