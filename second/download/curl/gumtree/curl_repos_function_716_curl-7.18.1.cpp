static char *detect_proxy(struct connectdata *conn)
{
  char *proxy = NULL;

#ifndef CURL_DISABLE_HTTP
  /* If proxy was not specified, we check for default proxy environment
   * variables, to enable i.e Lynx compliance:
   *
   * http_proxy=http://some.server.dom:port/
   * https_proxy=http://some.server.dom:port/
   * ftp_proxy=http://some.server.dom:port/
   * no_proxy=domain1.dom,host.domain2.dom
   *   (a comma-separated list of hosts which should
   *   not be proxied, or an asterisk to override
   *   all proxy variables)
   * all_proxy=http://some.server.dom:port/
   *   (seems to exist for the CERN www lib. Probably
   *   the first to check for.)
   *
   * For compatibility, the all-uppercase versions of these variables are
   * checked if the lowercase versions don't exist.
   */
  char *no_proxy=NULL;
  char *no_proxy_tok_buf;
  char proxy_env[128];

  no_proxy=curl_getenv("no_proxy");
  if(!no_proxy)
    no_proxy=curl_getenv("NO_PROXY");

  if(!no_proxy || !strequal("*", no_proxy)) {
    /* NO_PROXY wasn't specified or it wasn't just an asterisk */
    char *nope;

    nope=no_proxy?strtok_r(no_proxy, ", ", &no_proxy_tok_buf):NULL;
    while(nope) {
      size_t namelen;
      char *endptr = strchr(conn->host.name, ':');
      if(endptr)
        namelen=endptr-conn->host.name;
      else
        namelen=strlen(conn->host.name);

      if(strlen(nope) <= namelen) {
        char *checkn=
          conn->host.name + namelen - strlen(nope);
        if(checkprefix(nope, checkn)) {
          /* no proxy for this host! */
          break;
        }
      }
      nope=strtok_r(NULL, ", ", &no_proxy_tok_buf);
    }
    if(!nope) {
      /* It was not listed as without proxy */
      char *protop = conn->protostr;
      char *envp = proxy_env;
      char *prox;

      /* Now, build <protocol>_proxy and check for such a one to use */
      while(*protop)
        *envp++ = (char)tolower((int)*protop++);

      /* append _proxy */
      strcpy(envp, "_proxy");

      /* read the protocol proxy: */
      prox=curl_getenv(proxy_env);

      /*
       * We don't try the uppercase version of HTTP_PROXY because of
       * security reasons:
       *
       * When curl is used in a webserver application
       * environment (cgi or php), this environment variable can
       * be controlled by the web server user by setting the
       * http header 'Proxy:' to some value.
       *
       * This can cause 'internal' http/ftp requests to be
       * arbitrarily redirected by any external attacker.
       */
      if(!prox && !strequal("http_proxy", proxy_env)) {
        /* There was no lowercase variable, try the uppercase version: */
        for(envp = proxy_env; *envp; envp++)
          *envp = (char)toupper((int)*envp);
        prox=curl_getenv(proxy_env);
      }

      if(prox && *prox) { /* don't count "" strings */
        proxy = prox; /* use this */
      }
      else {
        proxy = curl_getenv("all_proxy"); /* default proxy to use */
        if(!proxy)
          proxy=curl_getenv("ALL_PROXY");
      }

      if(proxy && *proxy) {
        long bits = conn->protocol & (PROT_HTTPS|PROT_SSL|PROT_MISSING);

        if(conn->proxytype == CURLPROXY_HTTP) {
          /* force this connection's protocol to become HTTP */
          conn->protocol = PROT_HTTP | bits;
          conn->bits.proxy = conn->bits.httpproxy = TRUE;
        }
      }
    } /* if(!nope) - it wasn't specified non-proxy */
  } /* NO_PROXY wasn't specified or '*' */
  if(no_proxy)
    free(no_proxy);

#else /* !CURL_DISABLE_HTTP */

  (void)conn;
#endif /* CURL_DISABLE_HTTP */

  return proxy;
}