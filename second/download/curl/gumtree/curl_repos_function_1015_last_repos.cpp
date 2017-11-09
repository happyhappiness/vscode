curl_socket_t Curl_getconnectinfo(struct Curl_easy *data,
                                  struct connectdata **connp)
{
  curl_socket_t sockfd;

  DEBUGASSERT(data);

  /* this works for an easy handle:
   * - that has been used for curl_easy_perform()
   * - that is associated with a multi handle, and whose connection
   *   was detached with CURLOPT_CONNECT_ONLY
   */
  if(data->state.lastconnect && (data->multi_easy || data->multi)) {
    struct connectdata *c = data->state.lastconnect;
    struct connfind find;
    find.tofind = data->state.lastconnect;
    find.found = FALSE;

    Curl_conncache_foreach(data->multi_easy?
                           &data->multi_easy->conn_cache:
                           &data->multi->conn_cache, &find, conn_is_conn);

    if(!find.found) {
      data->state.lastconnect = NULL;
      return CURL_SOCKET_BAD;
    }

    if(connp)
      /* only store this if the caller cares for it */
      *connp = c;
    sockfd = c->sock[FIRSTSOCKET];
  }
  else
    return CURL_SOCKET_BAD;

  return sockfd;
}