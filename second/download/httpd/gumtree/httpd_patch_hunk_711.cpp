 PROXY_DECLARE(int) ap_proxy_hex2sec(const char *x)
 {
     int i, ch;
     unsigned int j;
 
     for (i = 0, j = 0; i < 8; i++) {
-	ch = x[i];
-	j <<= 4;
-	if (apr_isdigit(ch))
-	    j |= ch - '0';
-	else if (apr_isupper(ch))
-	    j |= ch - ('A' - 10);
-	else
-	    j |= ch - ('a' - 10);
+    ch = x[i];
+    j <<= 4;
+    if (apr_isdigit(ch))
+        j |= ch - '0';
+    else if (apr_isupper(ch))
+        j |= ch - ('A' - 10);
+    else
+        j |= ch - ('a' - 10);
     }
     if (j == 0xffffffff)
-	return -1;		/* so that it works with 8-byte ints */
+    return -1;      /* so that it works with 8-byte ints */
     else
-	return j;
+    return j;
 }
 
 /*
  * Converts a time integer to 8 hex digits
  */
 PROXY_DECLARE(void) ap_proxy_sec2hex(int t, char *y)
 {
     int i, ch;
     unsigned int j = t;
 
     for (i = 7; i >= 0; i--) {
-	ch = j & 0xF;
-	j >>= 4;
-	if (ch >= 10)
-	    y[i] = ch + ('A' - 10);
-	else
-	    y[i] = ch + '0';
+    ch = j & 0xF;
+    j >>= 4;
+    if (ch >= 10)
+        y[i] = ch + ('A' - 10);
+    else
+        y[i] = ch + '0';
     }
     y[8] = '\0';
 }
 
 PROXY_DECLARE(int) ap_proxyerror(request_rec *r, int statuscode, const char *message)
 {
     apr_table_setn(r->notes, "error-notes",
-	apr_pstrcat(r->pool, 
-		"The proxy server could not handle the request "
-		"<em><a href=\"", ap_escape_uri(r->pool, r->uri),
-		"\">", ap_escape_html(r->pool, r->method),
-		"&nbsp;", 
-		ap_escape_html(r->pool, r->uri), "</a></em>.<p>\n"
-		"Reason: <strong>",
-		ap_escape_html(r->pool, message), 
-		"</strong></p>", NULL));
+    apr_pstrcat(r->pool,
+        "The proxy server could not handle the request "
+        "<em><a href=\"", ap_escape_uri(r->pool, r->uri),
+        "\">", ap_escape_html(r->pool, r->method),
+        "&nbsp;",
+        ap_escape_html(r->pool, r->uri), "</a></em>.<p>\n"
+        "Reason: <strong>",
+        ap_escape_html(r->pool, message),
+        "</strong></p>", NULL));
 
     /* Allow "error-notes" string to be printed by ap_send_error_response() */
     apr_table_setn(r->notes, "verbose-error-to", apr_pstrdup(r->pool, "*"));
 
     r->status_line = apr_psprintf(r->pool, "%3.3u Proxy Error", statuscode);
     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-			 "proxy: %s returned by %s", message, r->uri);
+             "proxy: %s returned by %s", message, r->uri);
     return statuscode;
 }
 
 static const char *
      proxy_get_host_of_request(request_rec *r)
 {
     char *url, *user = NULL, *password = NULL, *err, *host;
     apr_port_t port;
 
     if (r->hostname != NULL)
-	return r->hostname;
+    return r->hostname;
 
     /* Set url to the first char after "scheme://" */
     if ((url = strchr(r->uri, ':')) == NULL
-	|| url[1] != '/' || url[2] != '/')
-	return NULL;
+    || url[1] != '/' || url[2] != '/')
+    return NULL;
 
-    url = apr_pstrdup(r->pool, &url[1]);	/* make it point to "//", which is what proxy_canon_netloc expects */
+    url = apr_pstrdup(r->pool, &url[1]);    /* make it point to "//", which is what proxy_canon_netloc expects */
 
     err = ap_proxy_canon_netloc(r->pool, &url, &user, &password, &host, &port);
 
     if (err != NULL)
-	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-		     "%s", err);
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+             "%s", err);
 
     r->hostname = host;
 
-    return host;		/* ought to return the port, too */
+    return host;        /* ought to return the port, too */
 }
 
 /* Return TRUE if addr represents an IP address (or an IP network address) */
 PROXY_DECLARE(int) ap_proxy_is_ipaddr(struct dirconn_entry *This, apr_pool_t *p)
 {
     const char *addr = This->name;
     long ip_addr[4];
     int i, quads;
     long bits;
 
-    /* if the address is given with an explicit netmask, use that */
-    /* Due to a deficiency in apr_inet_addr(), it is impossible to parse */
-    /* "partial" addresses (with less than 4 quads) correctly, i.e.  */
-    /* 192.168.123 is parsed as 192.168.0.123, which is not what I want. */
-    /* I therefore have to parse the IP address manually: */
-    /*if (proxy_readmask(This->name, &This->addr.s_addr, &This->mask.s_addr) == 0) */
-    /* addr and mask were set by proxy_readmask() */
-    /*return 1; */
+    /*
+     * if the address is given with an explicit netmask, use that
+     * Due to a deficiency in apr_inet_addr(), it is impossible to parse
+     * "partial" addresses (with less than 4 quads) correctly, i.e.
+     * 192.168.123 is parsed as 192.168.0.123, which is not what I want.
+     * I therefore have to parse the IP address manually:
+     * if (proxy_readmask(This->name, &This->addr.s_addr, &This->mask.s_addr) == 0)
+     * addr and mask were set by proxy_readmask()
+     * return 1;
+     */
 
-    /* Parse IP addr manually, optionally allowing */
-    /* abbreviated net addresses like 192.168. */
+    /*
+     * Parse IP addr manually, optionally allowing
+     * abbreviated net addresses like 192.168.
+     */
 
     /* Iterate over up to 4 (dotted) quads. */
     for (quads = 0; quads < 4 && *addr != '\0'; ++quads) {
-	char *tmp;
+    char *tmp;
 
-	if (*addr == '/' && quads > 0)	/* netmask starts here. */
-	    break;
+    if (*addr == '/' && quads > 0)  /* netmask starts here. */
+        break;
 
-	if (!apr_isdigit(*addr))
-	    return 0;		/* no digit at start of quad */
+    if (!apr_isdigit(*addr))
+        return 0;       /* no digit at start of quad */
 
-	ip_addr[quads] = strtol(addr, &tmp, 0);
+    ip_addr[quads] = strtol(addr, &tmp, 0);
 
-	if (tmp == addr)	/* expected a digit, found something else */
-	    return 0;
+    if (tmp == addr)    /* expected a digit, found something else */
+        return 0;
 
-	if (ip_addr[quads] < 0 || ip_addr[quads] > 255) {
-	    /* invalid octet */
-	    return 0;
-	}
+    if (ip_addr[quads] < 0 || ip_addr[quads] > 255) {
+        /* invalid octet */
+        return 0;
+    }
 
-	addr = tmp;
+    addr = tmp;
 
-	if (*addr == '.' && quads != 3)
-	    ++addr;		/* after the 4th quad, a dot would be illegal */
+    if (*addr == '.' && quads != 3)
+        ++addr;     /* after the 4th quad, a dot would be illegal */
     }
 
     for (This->addr.s_addr = 0, i = 0; i < quads; ++i)
-	This->addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
+    This->addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
 
-    if (addr[0] == '/' && apr_isdigit(addr[1])) {	/* net mask follows: */
-	char *tmp;
+    if (addr[0] == '/' && apr_isdigit(addr[1])) {   /* net mask follows: */
+    char *tmp;
 
-	++addr;
+    ++addr;
 
-	bits = strtol(addr, &tmp, 0);
+    bits = strtol(addr, &tmp, 0);
 
-	if (tmp == addr)	/* expected a digit, found something else */
-	    return 0;
+    if (tmp == addr)    /* expected a digit, found something else */
+        return 0;
 
-	addr = tmp;
+    addr = tmp;
 
-	if (bits < 0 || bits > 32)	/* netmask must be between 0 and 32 */
-	    return 0;
+    if (bits < 0 || bits > 32)  /* netmask must be between 0 and 32 */
+        return 0;
 
     }
     else {
-	/* Determine (i.e., "guess") netmask by counting the */
-	/* number of trailing .0's; reduce #quads appropriately */
-	/* (so that 192.168.0.0 is equivalent to 192.168.)        */
-	while (quads > 0 && ip_addr[quads - 1] == 0)
-	    --quads;
-
-	/* "IP Address should be given in dotted-quad form, optionally followed by a netmask (e.g., 192.168.111.0/24)"; */
-	if (quads < 1)
-	    return 0;
+    /*
+     * Determine (i.e., "guess") netmask by counting the
+     * number of trailing .0's; reduce #quads appropriately
+     * (so that 192.168.0.0 is equivalent to 192.168.)
+     */
+    while (quads > 0 && ip_addr[quads - 1] == 0)
+        --quads;
 
-	/* every zero-byte counts as 8 zero-bits */
-	bits = 8 * quads;
+    /* "IP Address should be given in dotted-quad form, optionally followed by a netmask (e.g., 192.168.111.0/24)"; */
+    if (quads < 1)
+        return 0;
 
-	if (bits != 32)		/* no warning for fully qualified IP address */
+    /* every zero-byte counts as 8 zero-bits */
+    bits = 8 * quads;
+
+    if (bits != 32)     /* no warning for fully qualified IP address */
             ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-	      "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld",
-		 inet_ntoa(This->addr), bits);
+          "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld",
+         inet_ntoa(This->addr), bits);
     }
 
     This->mask.s_addr = htonl(APR_INADDR_NONE << (32 - bits));
 
     if (*addr == '\0' && (This->addr.s_addr & ~This->mask.s_addr) != 0) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-	    "Warning: NetMask and IP-Addr disagree in %s/%ld",
-		inet_ntoa(This->addr), bits);
-	This->addr.s_addr &= This->mask.s_addr;
+        "Warning: NetMask and IP-Addr disagree in %s/%ld",
+        inet_ntoa(This->addr), bits);
+    This->addr.s_addr &= This->mask.s_addr;
         ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-	    "         Set to %s/%ld",
-		inet_ntoa(This->addr), bits);
+        "         Set to %s/%ld",
+        inet_ntoa(This->addr), bits);
     }
 
     if (*addr == '\0') {
-	This->matcher = proxy_match_ipaddr;
-	return 1;
+    This->matcher = proxy_match_ipaddr;
+    return 1;
     }
     else
-	return (*addr == '\0');	/* okay iff we've parsed the whole string */
+    return (*addr == '\0'); /* okay iff we've parsed the whole string */
 }
 
 /* Return TRUE if addr represents an IP address (or an IP network address) */
 static int proxy_match_ipaddr(struct dirconn_entry *This, request_rec *r)
 {
     int i, ip_addr[4];
