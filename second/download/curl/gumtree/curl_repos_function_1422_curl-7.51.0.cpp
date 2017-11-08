static CURLcode parse_connect_to_slist(struct Curl_easy *data,
                                       struct connectdata *conn,
                                       struct curl_slist *conn_to_host)
{
  CURLcode result = CURLE_OK;
  char *host = NULL;
  int port = 0;

  while(conn_to_host && !host) {
    result = parse_connect_to_string(data, conn, conn_to_host->data,
                                     &host, &port);
    if(result)
      return result;

    if(host && *host) {
      bool ipv6host;
      conn->conn_to_host.rawalloc = host;
      conn->conn_to_host.name = host;
      conn->bits.conn_to_host = TRUE;

      ipv6host = strchr(host, ':') != NULL;
      infof(data, "Connecting to hostname: %s%s%s\n",
            ipv6host ? "[" : "", host, ipv6host ? "]" : "");
    }
    else {
      /* no "connect to host" */
      conn->bits.conn_to_host = FALSE;
      free(host);
    }

    if(port >= 0) {
      conn->conn_to_port = port;
      conn->bits.conn_to_port = TRUE;
      infof(data, "Connecting to port: %d\n", port);
    }
    else {
      /* no "connect to port" */
      conn->bits.conn_to_port = FALSE;
    }

    conn_to_host = conn_to_host->next;
  }

  return result;
}