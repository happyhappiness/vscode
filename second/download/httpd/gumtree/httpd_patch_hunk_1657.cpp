      * Parse IP addr manually, optionally allowing
      * abbreviated net addresses like 192.168.
      */
 
     /* Iterate over up to 4 (dotted) quads. */
     for (quads = 0; quads < 4 && *addr != '\0'; ++quads) {
-    char *tmp;
+        char *tmp;
 
-    if (*addr == '/' && quads > 0)  /* netmask starts here. */
-        break;
+        if (*addr == '/' && quads > 0) {  /* netmask starts here. */
+            break;
+        }
 
-    if (!apr_isdigit(*addr))
-        return 0;       /* no digit at start of quad */
+        if (!apr_isdigit(*addr)) {
+            return 0;       /* no digit at start of quad */
+        }
 
-    ip_addr[quads] = strtol(addr, &tmp, 0);
+        ip_addr[quads] = strtol(addr, &tmp, 0);
 
-    if (tmp == addr)    /* expected a digit, found something else */
-        return 0;
+        if (tmp == addr) {  /* expected a digit, found something else */
+            return 0;
+        }
 
-    if (ip_addr[quads] < 0 || ip_addr[quads] > 255) {
-        /* invalid octet */
-        return 0;
-    }
+        if (ip_addr[quads] < 0 || ip_addr[quads] > 255) {
+            /* invalid octet */
+            return 0;
+        }
 
-    addr = tmp;
+        addr = tmp;
 
-    if (*addr == '.' && quads != 3)
-        ++addr;     /* after the 4th quad, a dot would be illegal */
+        if (*addr == '.' && quads != 3) {
+            ++addr;     /* after the 4th quad, a dot would be illegal */
+        }
     }
 
-    for (This->addr.s_addr = 0, i = 0; i < quads; ++i)
-    This->addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
+    for (This->addr.s_addr = 0, i = 0; i < quads; ++i) {
+        This->addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
+    }
 
     if (addr[0] == '/' && apr_isdigit(addr[1])) {   /* net mask follows: */
-    char *tmp;
+        char *tmp;
 
-    ++addr;
+        ++addr;
 
-    bits = strtol(addr, &tmp, 0);
+        bits = strtol(addr, &tmp, 0);
 
-    if (tmp == addr)    /* expected a digit, found something else */
-        return 0;
+        if (tmp == addr) {   /* expected a digit, found something else */
+            return 0;
+        }
 
-    addr = tmp;
+        addr = tmp;
 
-    if (bits < 0 || bits > 32)  /* netmask must be between 0 and 32 */
-        return 0;
+        if (bits < 0 || bits > 32) { /* netmask must be between 0 and 32 */
+            return 0;
+        }
 
     }
     else {
-    /*
-     * Determine (i.e., "guess") netmask by counting the
-     * number of trailing .0's; reduce #quads appropriately
-     * (so that 192.168.0.0 is equivalent to 192.168.)
-     */
-    while (quads > 0 && ip_addr[quads - 1] == 0)
-        --quads;
+        /*
+         * Determine (i.e., "guess") netmask by counting the
+         * number of trailing .0's; reduce #quads appropriately
+         * (so that 192.168.0.0 is equivalent to 192.168.)
+         */
+        while (quads > 0 && ip_addr[quads - 1] == 0) {
+            --quads;
+        }
 
-    /* "IP Address should be given in dotted-quad form, optionally followed by a netmask (e.g., 192.168.111.0/24)"; */
-    if (quads < 1)
-        return 0;
+        /* "IP Address should be given in dotted-quad form, optionally followed by a netmask (e.g., 192.168.111.0/24)"; */
+        if (quads < 1) {
+            return 0;
+        }
 
-    /* every zero-byte counts as 8 zero-bits */
-    bits = 8 * quads;
+        /* every zero-byte counts as 8 zero-bits */
+        bits = 8 * quads;
 
-    if (bits != 32)     /* no warning for fully qualified IP address */
+        if (bits != 32) {     /* no warning for fully qualified IP address */
             ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-          "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld",
-         inet_ntoa(This->addr), bits);
+                         "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld",
+                         inet_ntoa(This->addr), bits);
+        }
     }
 
     This->mask.s_addr = htonl(APR_INADDR_NONE << (32 - bits));
 
     if (*addr == '\0' && (This->addr.s_addr & ~This->mask.s_addr) != 0) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-        "Warning: NetMask and IP-Addr disagree in %s/%ld",
-        inet_ntoa(This->addr), bits);
-    This->addr.s_addr &= This->mask.s_addr;
+                     "Warning: NetMask and IP-Addr disagree in %s/%ld",
+                     inet_ntoa(This->addr), bits);
+        This->addr.s_addr &= This->mask.s_addr;
         ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-        "         Set to %s/%ld",
-        inet_ntoa(This->addr), bits);
+                     "         Set to %s/%ld", inet_ntoa(This->addr), bits);
     }
 
     if (*addr == '\0') {
-    This->matcher = proxy_match_ipaddr;
-    return 1;
+        This->matcher = proxy_match_ipaddr;
+        return 1;
+    }
+    else {
+        return (*addr == '\0'); /* okay iff we've parsed the whole string */
     }
-    else
-    return (*addr == '\0'); /* okay iff we've parsed the whole string */
 }
 
 /* Return TRUE if addr represents an IP address (or an IP network address) */
 static int proxy_match_ipaddr(struct dirconn_entry *This, request_rec *r)
 {
     int i, ip_addr[4];
     struct in_addr addr, *ip;
     const char *host = proxy_get_host_of_request(r);
 
-    if (host == NULL)   /* oops! */
+    if (host == NULL) {   /* oops! */
        return 0;
+    }
 
     memset(&addr, '\0', sizeof addr);
     memset(ip_addr, '\0', sizeof ip_addr);
 
     if (4 == sscanf(host, "%d.%d.%d.%d", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3])) {
-    for (addr.s_addr = 0, i = 0; i < 4; ++i)
-        addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
+        for (addr.s_addr = 0, i = 0; i < 4; ++i) {
+            addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
+        }
 
-    if (This->addr.s_addr == (addr.s_addr & This->mask.s_addr)) {
+        if (This->addr.s_addr == (addr.s_addr & This->mask.s_addr)) {
 #if DEBUGGING
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "1)IP-Match: %s[%s] <-> ", host, inet_ntoa(addr));
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "%s/", inet_ntoa(This->addr));
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "%s", inet_ntoa(This->mask));
 #endif
-        return 1;
-    }
+            return 1;
+        }
 #if DEBUGGING
-    else {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+        else {
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "1)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(addr));
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "%s/", inet_ntoa(This->addr));
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                          "%s", inet_ntoa(This->mask));
-    }
+        }
 #endif
     }
     else {
-    struct apr_sockaddr_t *reqaddr;
+        struct apr_sockaddr_t *reqaddr;
 
         if (apr_sockaddr_info_get(&reqaddr, host, APR_UNSPEC, 0, 0, r->pool)
-        != APR_SUCCESS) {
+            != APR_SUCCESS) {
 #if DEBUGGING
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-             "2)IP-NoMatch: hostname=%s msg=Host not found",
-             host);
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+             "2)IP-NoMatch: hostname=%s msg=Host not found", host);
 #endif
-        return 0;
-    }
+            return 0;
+        }
 
-    /* Try to deal with multiple IP addr's for a host */
-    /* FIXME: This needs to be able to deal with IPv6 */
-    while (reqaddr) {
-        ip = (struct in_addr *) reqaddr->ipaddr_ptr;
-        if (This->addr.s_addr == (ip->s_addr & This->mask.s_addr)) {
+        /* Try to deal with multiple IP addr's for a host */
+        /* FIXME: This needs to be able to deal with IPv6 */
+        while (reqaddr) {
+            ip = (struct in_addr *) reqaddr->ipaddr_ptr;
+            if (This->addr.s_addr == (ip->s_addr & This->mask.s_addr)) {
 #if DEBUGGING
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "3)IP-Match: %s[%s] <-> ", host,
-                 inet_ntoa(*ip));
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "%s/", inet_ntoa(This->addr));
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "%s", inet_ntoa(This->mask));
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                             "3)IP-Match: %s[%s] <-> ", host, inet_ntoa(*ip));
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                             "%s/", inet_ntoa(This->addr));
+                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                             "%s", inet_ntoa(This->mask));
 #endif
-        return 1;
-        }
+                return 1;
+            }
 #if DEBUGGING
-        else {
+            else {
                 ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "3)IP-NoMatch: %s[%s] <-> ", host,
-                 inet_ntoa(*ip));
+                             "3)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(*ip));
                 ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "%s/", inet_ntoa(This->addr));
+                             "%s/", inet_ntoa(This->addr));
                 ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "%s", inet_ntoa(This->mask));
-        }
+                             "%s", inet_ntoa(This->mask));
+            }
 #endif
-        reqaddr = reqaddr->next;
-    }
+            reqaddr = reqaddr->next;
+        }
     }
 
     return 0;
 }
 
 /* Return TRUE if addr represents a domain name */
 PROXY_DECLARE(int) ap_proxy_is_domainname(struct dirconn_entry *This, apr_pool_t *p)
 {
     char *addr = This->name;
     int i;
 
     /* Domain name must start with a '.' */
-    if (addr[0] != '.')
+    if (addr[0] != '.') {
         return 0;
+    }
 
     /* rfc1035 says DNS names must consist of "[-a-zA-Z0-9]" and '.' */
-    for (i = 0; apr_isalnum(addr[i]) || addr[i] == '-' || addr[i] == '.'; ++i)
+    for (i = 0; apr_isalnum(addr[i]) || addr[i] == '-' || addr[i] == '.'; ++i) {
         continue;
+    }
 
 #if 0
     if (addr[i] == ':') {
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                      "@@@@ handle optional port in proxy_is_domainname()");
     /* @@@@ handle optional port */
     }
 #endif
 
-    if (addr[i] != '\0')
+    if (addr[i] != '\0') {
         return 0;
+    }
 
     /* Strip trailing dots */
-    for (i = strlen(addr) - 1; i > 0 && addr[i] == '.'; --i)
+    for (i = strlen(addr) - 1; i > 0 && addr[i] == '.'; --i) {
         addr[i] = '\0';
+    }
 
     This->matcher = proxy_match_domainname;
     return 1;
 }
 
 /* Return TRUE if host "host" is in domain "domain" */
 static int proxy_match_domainname(struct dirconn_entry *This, request_rec *r)
 {
     const char *host = proxy_get_host_of_request(r);
     int d_len = strlen(This->name), h_len;
 
-    if (host == NULL)       /* some error was logged already */
+    if (host == NULL) {      /* some error was logged already */
         return 0;
+    }
 
     h_len = strlen(host);
 
     /* @@@ do this within the setup? */
     /* Ignore trailing dots in domain comparison: */
-    while (d_len > 0 && This->name[d_len - 1] == '.')
+    while (d_len > 0 && This->name[d_len - 1] == '.') {
         --d_len;
-    while (h_len > 0 && host[h_len - 1] == '.')
+    }
+    while (h_len > 0 && host[h_len - 1] == '.') {
         --h_len;
+    }
     return h_len > d_len
         && strncasecmp(&host[h_len - d_len], This->name, d_len) == 0;
 }
 
 /* Return TRUE if host represents a host name */
 PROXY_DECLARE(int) ap_proxy_is_hostname(struct dirconn_entry *This, apr_pool_t *p)
 {
     struct apr_sockaddr_t *addr;
     char *host = This->name;
     int i;
 
     /* Host names must not start with a '.' */
-    if (host[0] == '.')
+    if (host[0] == '.') {
         return 0;
-
+    }
     /* rfc1035 says DNS names must consist of "[-a-zA-Z0-9]" and '.' */
     for (i = 0; apr_isalnum(host[i]) || host[i] == '-' || host[i] == '.'; ++i);
 
-    if (host[i] != '\0' || apr_sockaddr_info_get(&addr, host, APR_UNSPEC, 0, 0, p) != APR_SUCCESS)
+    if (host[i] != '\0' || apr_sockaddr_info_get(&addr, host, APR_UNSPEC, 0, 0, p) != APR_SUCCESS) {
         return 0;
+    }
 
     This->hostaddr = addr;
 
     /* Strip trailing dots */
-    for (i = strlen(host) - 1; i > 0 && host[i] == '.'; --i)
+    for (i = strlen(host) - 1; i > 0 && host[i] == '.'; --i) {
         host[i] = '\0';
+    }
 
     This->matcher = proxy_match_hostname;
     return 1;
 }
 
 /* Return TRUE if host "host" is equal to host2 "host2" */
