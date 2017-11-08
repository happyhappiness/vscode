CURLcode Curl_is_resolved(struct connectdata *conn,
                          struct Curl_dns_entry **dns)
{
  struct SessionHandle *data = conn->data;

  *dns = NULL;

  ares_waitperform(conn, 0);

  if(conn->async.done) {
    /* we're done, kill the ares handle */
    if(!conn->async.dns) {
      failf(data, "Could not resolve host: %s (%s)", conn->host.dispname,
            ares_strerror(conn->async.status));
      return CURLE_COULDNT_RESOLVE_HOST;
    }
    *dns = conn->async.dns;
  }

  return CURLE_OK;
}