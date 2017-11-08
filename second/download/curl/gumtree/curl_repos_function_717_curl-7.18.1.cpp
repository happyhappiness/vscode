static CURLcode parse_proxy(struct SessionHandle *data,
                            struct connectdata *conn, char *proxy)
{
  char *prox_portno;
  char *endofprot;

  /* We use 'proxyptr' to point to the proxy name from now on... */
  char *proxyptr=proxy;
  char *portptr;
  char *atsign;

  /* We do the proxy host string parsing here. We want the host name and the
   * port name. Accept a protocol:// prefix, even though it should just be
   * ignored.
   */

  /* Skip the protocol part if present */
  endofprot=strstr(proxyptr, "://");
  if(endofprot)
    proxyptr = endofprot+3;

  /* Is there a username and password given in this proxy url? */
  atsign = strchr(proxyptr, '@');
  if(atsign) {
    char proxyuser[MAX_CURL_USER_LENGTH];
    char proxypasswd[MAX_CURL_PASSWORD_LENGTH];
    proxypasswd[0] = 0;

    if(1 <= sscanf(proxyptr,
                   "%" MAX_CURL_USER_LENGTH_TXT"[^:]:"
                   "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^@]",
                   proxyuser, proxypasswd)) {
      CURLcode res = CURLE_OK;

      /* found user and password, rip them out.  note that we are
         unescaping them, as there is otherwise no way to have a
         username or password with reserved characters like ':' in
         them. */
      Curl_safefree(conn->proxyuser);
      conn->proxyuser = curl_easy_unescape(data, proxyuser, 0, NULL);

      if(!conn->proxyuser)
        res = CURLE_OUT_OF_MEMORY;
      else {
        Curl_safefree(conn->proxypasswd);
        conn->proxypasswd = curl_easy_unescape(data, proxypasswd, 0, NULL);

        if(!conn->proxypasswd)
          res = CURLE_OUT_OF_MEMORY;
      }

      if(CURLE_OK == res) {
        conn->bits.proxy_user_passwd = TRUE; /* enable it */
        atsign = strdup(atsign+1); /* the right side of the @-letter */

        if(atsign) {
          free(proxy); /* free the former proxy string */
          proxy = proxyptr = atsign; /* now use this instead */
        }
        else
          res = CURLE_OUT_OF_MEMORY;
      }

      if(res) {
        free(proxy); /* free the allocated proxy string */
        return res;
      }
    }
  }

  /* start scanning for port number at this point */
  portptr = proxyptr;

  /* detect and extract RFC2732-style IPv6-addresses */
  if(*proxyptr == '[') {
    char *ptr = ++proxyptr; /* advance beyond the initial bracket */
    while(*ptr && (ISXDIGIT(*ptr) || (*ptr == ':')))
      ptr++;
    if(*ptr == ']') {
      /* yeps, it ended nicely with a bracket as well */
      *ptr = 0;
      portptr = ptr+1;
    }
    /* Note that if this didn't end with a bracket, we still advanced the
     * proxyptr first, but I can't see anything wrong with that as no host
     * name nor a numeric can legally start with a bracket.
     */
  }

  /* Get port number off proxy.server.com:1080 */
  prox_portno = strchr(portptr, ':');
  if(prox_portno) {
    *prox_portno = 0x0; /* cut off number from host name */
    prox_portno ++;
    /* now set the local port number */
    conn->port = atoi(prox_portno);
  }
  else {
    /* without a port number after the host name, some people seem to use
       a slash so we strip everything from the first slash */
    atsign = strchr(proxyptr, '/');
    if(atsign)
      *atsign = 0x0; /* cut off path part from host name */

    if(data->set.proxyport)
      /* None given in the proxy string, then get the default one if it is
         given */
      conn->port = data->set.proxyport;
  }

  /* now, clone the cleaned proxy host name */
  conn->proxy.rawalloc = strdup(proxyptr);
  conn->proxy.name = conn->proxy.rawalloc;

  free(proxy);
  if(!conn->proxy.rawalloc)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}