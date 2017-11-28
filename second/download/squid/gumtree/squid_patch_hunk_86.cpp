 
         } else if (!strcasecmp(token, "carp")) {
             if (p->type != PEER_PARENT)
                 fatalf("parse_peer: non-parent carp peer %s/%d\n", p->host, p->http_port);
 
             p->options.carp = 1;
-
+        } else if (!strncasecmp(token, "carp-key=", 9)) {
+            if (p->options.carp != 1)
+                fatalf("parse_peer: carp-key specified on non-carp peer %s/%d\n", p->host, p->http_port);
+            p->options.carp_key.set=1;
+            char *nextkey=token+strlen("carp-key="), *key=nextkey;
+            for (; key; key = nextkey) {
+                nextkey=strchr(key,',');
+                if (nextkey) ++nextkey; // skip the comma, any
+                if (0==strncasecmp(key,"scheme",6)) {
+                    p->options.carp_key.scheme=1;
+                } else if (0==strncasecmp(key,"host",4)) {
+                    p->options.carp_key.host=1;
+                } else if (0==strncasecmp(key,"port",4)) {
+                    p->options.carp_key.port=1;
+                } else if (0==strncasecmp(key,"path",4)) {
+                    p->options.carp_key.path=1;
+                } else if (0==strncasecmp(key,"params",6)) {
+                    p->options.carp_key.params=1;
+                } else {
+                    fatalf("invalid carp-key '%s'",key);
+                }
+            }
         } else if (!strcasecmp(token, "userhash")) {
+#if USE_AUTH
             if (p->type != PEER_PARENT)
                 fatalf("parse_peer: non-parent userhash peer %s/%d\n", p->host, p->http_port);
 
             p->options.userhash = 1;
-
+#else
+            fatalf("parse_peer: userhash requires authentication. peer %s/%d\n", p->host, p->http_port);
+#endif
         } else if (!strcasecmp(token, "sourcehash")) {
             if (p->type != PEER_PARENT)
                 fatalf("parse_peer: non-parent sourcehash peer %s/%d\n", p->host, p->http_port);
 
             p->options.sourcehash = 1;
 
-#if DELAY_POOLS
-
         } else if (!strcasecmp(token, "no-delay")) {
+#if USE_DELAY_POOLS
             p->options.no_delay = 1;
+#else
+            debugs(0, DBG_CRITICAL, "WARNING: cache_peer option 'no-delay' requires --enable-delay-pools");
 #endif
-
         } else if (!strncasecmp(token, "login=", 6)) {
             p->login = xstrdup(token + 6);
             rfc1738_unescape(p->login);
         } else if (!strncasecmp(token, "connect-timeout=", 16)) {
             p->connect_timeout = xatoi(token + 16);
         } else if (!strncasecmp(token, "connect-fail-limit=", 19)) {
