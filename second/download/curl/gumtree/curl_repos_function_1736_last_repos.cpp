CURLcode Curl_resolver_is_resolved(struct connectdata *conn,
                                   struct Curl_dns_entry **dns)
{
  struct Curl_easy *data = conn->data;
  struct ResolverResults *res = (struct ResolverResults *)
    conn->async.os_specific;
  CURLcode result = CURLE_OK;

  *dns = NULL;

  waitperform(conn, 0);

  if(res && !res->num_pending) {
    (void)Curl_addrinfo_callback(conn, res->last_status, res->temp_ai);
    /* temp_ai ownership is moved to the connection, so we need not free-up
       them */
    res->temp_ai = NULL;
    if(!conn->async.dns) {
      failf(data, "Could not resolve: %s (%s)",
            conn->async.hostname, ares_strerror(conn->async.status));
      result = conn->bits.proxy?CURLE_COULDNT_RESOLVE_PROXY:
        CURLE_COULDNT_RESOLVE_HOST;
    }
    else
      *dns = conn->async.dns;

    destroy_async_data(&conn->async);
  }

  return result;
}