 
         /* For intranet (Internal proxies) ignore all restrictions below */
         if (!internal
               && ((temp_sa->family == APR_INET
                    /* For internet (non-Internal proxies) deny all
                     * RFC3330 designated local/private subnets:
-                    * 10.0.0.0/8   169.254.0.0/16  192.168.0.0/16 
+                    * 10.0.0.0/8   169.254.0.0/16  192.168.0.0/16
                     * 127.0.0.0/8  172.16.0.0/12
                     */
                       && (addrbyte[0] == 10
                        || addrbyte[0] == 127
                        || (addrbyte[0] == 169 && addrbyte[1] == 254)
                        || (addrbyte[0] == 172 && (addrbyte[1] & 0xf0) == 16)
                        || (addrbyte[0] == 192 && addrbyte[1] == 168)))
 #if APR_HAVE_IPV6
                || (temp_sa->family == APR_INET6
-                   /* For internet (non-Internal proxies) we translated 
+                   /* For internet (non-Internal proxies) we translated
                     * IPv4-over-IPv6-mapped addresses as IPv4, above.
                     * Accept only Global Unicast 2000::/3 defined by RFC4291
                     */
                       && ((temp_sa->sa.sin6.sin6_addr.s6_addr[0] & 0xe0) != 0x20))
 #endif
         )) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r, APLOGNO(01569)
                           "RemoteIP: Header %s value of %s appears to be "
                           "a private IP or nonsensical.  Ignored",
                           config->header_name, parse_remote);
-            if (remote)
+            if (remote) {
                 *(remote + strlen(remote)) = ',';
-            else
+            }
+            else {
                 remote = parse_remote;
+            }
+
             break;
         }
 
-        if (!conn) {
-            conn = (remoteip_conn_t *) apr_palloc(c->pool, sizeof(*conn));
-            apr_pool_userdata_set(conn, "mod_remoteip-conn", NULL, c->pool);
-            conn->orig_addr = c->remote_addr;
-            conn->orig_ip = c->remote_ip;
+        /* save away our results */
+        if (!req) {
+            req = (remoteip_req_t *) apr_palloc(r->pool, sizeof(remoteip_req_t));
         }
 
-        /* Set remote_ip string */
+        /* Set useragent_ip string */
         if (!internal) {
-            if (proxy_ips)
-                proxy_ips = apr_pstrcat(r->pool, proxy_ips, ", ", 
-                                        c->remote_ip, NULL);
-            else
-                proxy_ips = c->remote_ip;
+            if (proxy_ips) {
+                proxy_ips = apr_pstrcat(r->pool, proxy_ips, ", ",
+                                        c->client_ip, NULL);
+            }
+            else {
+                proxy_ips = c->client_ip;
+            }
         }
 
-        c->remote_addr = temp_sa;
-        apr_sockaddr_ip_get(&c->remote_ip, c->remote_addr);
+        req->useragent_addr = temp_sa;
+        apr_sockaddr_ip_get(&req->useragent_ip, req->useragent_addr);
     }
 
     /* Nothing happened? */
-    if (!conn || (c->remote_addr == conn->orig_addr))
+    if (!req) {
         return OK;
+    }
 
-    /* Fixups here, remote becomes the new Via header value, etc 
-     * In the heavy operations above we used request scope, to limit
-     * conn pool memory growth on keepalives, so here we must scope
-     * the final results to the connection pool lifetime.
-     * To limit memory growth, we keep recycling the same buffer
-     * for the final apr_sockaddr_t in the remoteip conn rec.
-     */
-    c->remote_ip = apr_pstrdup(c->pool, c->remote_ip);
-    conn->proxied_ip = c->remote_ip;
-    memcpy(&conn->proxied_addr, &temp_sa, sizeof(temp_sa));
-    conn->proxied_addr.pool = c->pool;
-    c->remote_addr = &conn->proxied_addr;
-
-    if (remote)
-        remote = apr_pstrdup(c->pool, remote);
-    conn->proxied_remote = remote;
-    conn->prior_remote = apr_pstrdup(c->pool, apr_table_get(r->headers_in, 
-                                                      config->header_name));
-    if (proxy_ips)
-        proxy_ips = apr_pstrdup(c->pool, proxy_ips);
-    conn->proxy_ips = proxy_ips;
-
-    /* Unset remote_host string DNS lookups */
-    c->remote_host = NULL;
-    c->remote_logname = NULL;
+    req->proxied_remote = remote;
+    req->proxy_ips = proxy_ips;
 
-ditto_request_rec:
-    if (conn->proxied_remote)
+    if (req->proxied_remote) {
         apr_table_setn(r->headers_in, config->header_name,
-                       conn->proxied_remote);
-    else
+                       req->proxied_remote);
+    }
+    else {
         apr_table_unset(r->headers_in, config->header_name);
-    if (conn->proxy_ips) {
-        apr_table_setn(r->notes, "remoteip-proxy-ip-list", conn->proxy_ips);
-        if (config->proxies_header_name)
+    }
+    if (req->proxy_ips) {
+        apr_table_setn(r->notes, "remoteip-proxy-ip-list", req->proxy_ips);
+        if (config->proxies_header_name) {
             apr_table_setn(r->headers_in, config->proxies_header_name,
-                           conn->proxy_ips);
+                           req->proxy_ips);
+        }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r,
-                  conn->proxy_ips 
+    r->useragent_addr = req->useragent_addr;
+    r->useragent_ip = req->useragent_ip;
+
+    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                  req->proxy_ips
                       ? "Using %s as client's IP by proxies %s"
                       : "Using %s as client's IP by internal proxies",
-                  conn->proxied_ip, conn->proxy_ips);
+                  req->useragent_ip, req->proxy_ips);
     return OK;
 }
 
 static const command_rec remoteip_cmds[] =
 {
     AP_INIT_TAKE1("RemoteIPHeader", header_name_set, NULL, RSRC_CONF,
