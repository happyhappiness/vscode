CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
                                     int tunnelsocket,
                                     char *hostname, int remote_port)
{
  int httperror=0;
  int subversion=0;
  struct SessionHandle *data=conn->data;

  infof(data, "Establish HTTP proxy tunnel to %s:%d\n", hostname, remote_port);

  /* OK, now send the connect request to the proxy */
  Curl_sendf(tunnelsocket, conn,
             "CONNECT %s:%d HTTP/1.0\015\012"
             "%s"
             "%s"
             "\r\n",
             hostname, remote_port,
             (conn->bits.proxy_user_passwd)?conn->allocptr.proxyuserpwd:"",
             (data->set.useragent?conn->allocptr.uagent:"")
             );

  /* wait for the proxy to send us a HTTP/1.0 200 OK header */
  while(GetLine(tunnelsocket, data->state.buffer, conn)) {
    if('\r' == data->state.buffer[0])
      break; /* end of headers */
    if(data->set.verbose)
      fprintf(data->set.err, "< %s\n", data->state.buffer);

    if(2 == sscanf(data->state.buffer, "HTTP/1.%d %d",
                   &subversion,
                   &httperror)) {
      ;
    }
  }
  if(200 != httperror) {
    if(407 == httperror)
      /* Added Nov 6 1998 */
      failf(data, "Proxy requires authorization!");
    else 
      failf(data, "Received error code %d from proxy", httperror);
    return CURLE_READ_ERROR;
  }

  infof (data, "Proxy replied to CONNECT request\n");
  return CURLE_OK;
}