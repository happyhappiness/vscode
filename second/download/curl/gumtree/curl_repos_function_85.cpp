CURLcode http_connect(struct connectdata *conn)
{
  struct UrlData *data;

  data=conn->data;

  /* If we are not using a proxy and we want a secure connection,
   * perform SSL initialization & connection now.
   * If using a proxy with https, then we must tell the proxy to CONNECT
   * us to the host we want to talk to.  Only after the connect
   * has occured, can we start talking SSL
   */
   if (conn->protocol & PROT_HTTPS) {
     if (data->bits.httpproxy) {

        /* OK, now send the connect statment */
        sendf(data->firstsocket, data,
              "CONNECT %s:%d HTTP/1.0\015\012"
              "%s"
	      "%s"
              "\r\n",
              data->hostname, data->remote_port,
              (data->bits.proxy_user_passwd)?data->ptr_proxyuserpwd:"",
	      (data->useragent?data->ptr_uagent:"")
              );

        /* wait for the proxy to send us a HTTP/1.0 200 OK header */
	/* Daniel rewrote this part Nov 5 1998 to make it more obvious */
	{
	  int httperror=0;
	  int subversion=0;
	  while(GetLine(data->firstsocket, data->buffer, data)) {
	    if('\r' == data->buffer[0])
	      break; /* end of headers */
	    if(2 == sscanf(data->buffer, "HTTP/1.%d %d",
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
	}
        infof (data, "Proxy has replied to CONNECT request\n");
     }

      /* now, perform the SSL initialization for this socket */
     if(UrgSSLConnect (data)) {
       return CURLE_SSL_CONNECT_ERROR;
     }
  }

   if(data->bits.user_passwd && !data->bits.this_is_a_follow) {
     /* Authorization: is requested, this is not a followed location, get the
        original host name */
     data->auth_host = strdup(data->hostname);
   }

   return CURLE_OK;
}