static CURLcode resolver_error(struct connectdata *conn)
{
  const char *host_or_proxy;
  CURLcode result;

  if(conn->bits.httpproxy) {
    host_or_proxy = "proxy";
    result = CURLE_COULDNT_RESOLVE_PROXY;
  }
  else {
    host_or_proxy = "host";
    result = CURLE_COULDNT_RESOLVE_HOST;
  }

  failf(conn->data, "Could not resolve %s: %s", host_or_proxy,
        conn->async.hostname);

  return result;
}