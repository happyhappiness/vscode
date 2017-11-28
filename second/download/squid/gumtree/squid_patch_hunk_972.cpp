 
 #if USE_OPENSSL
     if (Config.ssl_client.foreignIntermediateCertsPath)
         Ssl::loadSquidUntrusted(Config.ssl_client.foreignIntermediateCertsPath);
 #endif
 
+    if (Security::ProxyOutgoingConfig.encryptTransport) {
+        debugs(3, DBG_IMPORTANT, "Initializing https:// proxy context");
+        Config.ssl_client.sslContext = Security::ProxyOutgoingConfig.createClientContext(false);
+        if (!Config.ssl_client.sslContext) {
 #if USE_OPENSSL
-    debugs(3, DBG_IMPORTANT, "Initializing https proxy context");
-
-    Config.ssl_client.sslContext = sslCreateClientContext(Config.ssl_client.cert, Config.ssl_client.key, Config.ssl_client.version, Config.ssl_client.cipher, NULL, Config.ssl_client.flags, Config.ssl_client.cafile, Config.ssl_client.capath, Config.ssl_client.crlfile);
-    // Pre-parse SSL client options to be applied when the client SSL objects created.
-    // Options must not used in the case of peek or stare bump mode.
-    Config.ssl_client.parsedOptions = Ssl::parse_options(::Config.ssl_client.options);
-    Ssl::useSquidUntrusted(Config.ssl_client.sslContext);
+            fatal("ERROR: Could not initialize https:// proxy context");
+#else
+            debugs(3, DBG_IMPORTANT, "ERROR: proxying https:// currently still requires --with-openssl");
+#endif
+        }
+#if USE_OPENSSL
+        Ssl::useSquidUntrusted(Config.ssl_client.sslContext.get());
+#endif
+    }
 
     for (CachePeer *p = Config.peers; p != NULL; p = p->next) {
-        if (p->use_ssl) {
-            debugs(3, DBG_IMPORTANT, "Initializing cache_peer " << p->name << " SSL context");
-            p->sslContext = sslCreateClientContext(p->sslcert, p->sslkey, p->sslversion, p->sslcipher, p->ssloptions, p->sslflags, p->sslcafile, p->sslcapath, p->sslcrlfile);
+
+        // default value for ssldomain= is the peer host/IP
+        if (p->secure.sslDomain.isEmpty())
+            p->secure.sslDomain = p->host;
+
+        if (p->secure.encryptTransport) {
+            debugs(3, DBG_IMPORTANT, "Initializing cache_peer " << p->name << " TLS context");
+            p->sslContext = p->secure.createClientContext(true);
+            if (!p->sslContext) {
+                debugs(3, DBG_CRITICAL, "ERROR: Could not initialize cache_peer " << p->name << " TLS context");
+                self_destruct();
+                return;
+            }
         }
     }
 
+#if USE_OPENSSL
     for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
-        if (!s->flags.tunnelSslBumping)
+        if (!s->secure.encryptTransport)
             continue;
-
-        debugs(3, DBG_IMPORTANT, "Initializing http_port " << s->s << " SSL context");
+        debugs(3, DBG_IMPORTANT, "Initializing " << AnyP::UriScheme(s->transport.protocol) << "_port " << s->s << " TLS context");
         s->configureSslServerContext();
     }
-
-    for (AnyP::PortCfgPointer s = HttpsPortList; s != NULL; s = s->next) {
-        debugs(3, DBG_IMPORTANT, "Initializing https_port " << s->s << " SSL context");
-        s->configureSslServerContext();
-    }
-
 #endif
 
     // prevent infinite fetch loops in the request parser
     // due to buffer full but not enough data recived to finish parse
     if (Config.maxRequestBufferSize <= Config.maxRequestHeaderSize) {
         fatalf("Client request buffer of %u bytes cannot hold a request with %u bytes of headers." \
