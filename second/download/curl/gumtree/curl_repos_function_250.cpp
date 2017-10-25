bool Curl_retry_request(struct connectdata *conn,
                        char **url)
{
  bool retry = FALSE;

  if((conn->keep.bytecount+conn->headerbytecount == 0) &&
     conn->bits.reuse) {
    /* We got no data and we attempted to re-use a connection. This might
       happen if the connection was left alive when we were done using it
       before, but that was closed when we wanted to read from it again. Bad
       luck. Retry the same request on a fresh connect! */
    infof(conn->data, "Connection died, retrying a fresh connect\n");
    *url = strdup(conn->data->change.url);

    conn->bits.close = TRUE; /* close this connection */
    conn->bits.retry = TRUE; /* mark this as a connection we're about
                                to retry. Marking it this way should
                                prevent i.e HTTP transfers to return
                                error just because nothing has been
                                transfered! */
    retry = TRUE;
  }

  return retry;
}