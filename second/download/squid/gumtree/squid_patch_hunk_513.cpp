     b->s = s;
     if (name)
         b->name = xstrdup(name);
     if (defaultsite)
         b->defaultsite = xstrdup(defaultsite);
 
-    b->intercepted = intercepted;
-    b->spoof_client_ip = spoof_client_ip;
-    b->accel = accel;
+    b->flags = flags;
     b->allow_direct = allow_direct;
     b->vhost = vhost;
-    b->sslBump = sslBump;
     b->vport = vport;
     b->connection_auth_disabled = connection_auth_disabled;
     b->disable_pmtu_discovery = disable_pmtu_discovery;
+    b->tcp_keepalive = tcp_keepalive;
 
-    memcpy( &(b->tcp_keepalive), &(tcp_keepalive), sizeof(tcp_keepalive));
+#if USE_SSL
+    if (cert)
+        b->cert = xstrdup(cert);
+    if (key)
+        b->key = xstrdup(key);
+    b->version = version;
+    if (cipher)
+        b->cipher = xstrdup(cipher);
+    if (options)
+        b->options = xstrdup(options);
+    if (clientca)
+        b->clientca = xstrdup(clientca);
+    if (cafile)
+        b->cafile = xstrdup(cafile);
+    if (capath)
+        b->capath = xstrdup(capath);
+    if (crlfile)
+        b->crlfile = xstrdup(crlfile);
+    if (dhfile)
+        b->dhfile = xstrdup(dhfile);
+    if (sslflags)
+        b->sslflags = xstrdup(sslflags);
+    if (sslContextSessionId)
+        b->sslContextSessionId = xstrdup(sslContextSessionId);
 
 #if 0
-    // AYJ: 2009-07-18: for now SSL does not clone. Configure separate ports with IPs and SSL settings
-
-#if USE_SSL
-    char *cert;
-    char *key;
-    int version;
-    char *cipher;
-    char *options;
-    char *clientca;
-    char *cafile;
-    char *capath;
-    char *crlfile;
-    char *dhfile;
-    char *sslflags;
-    char *sslContextSessionId;
+    // TODO: AYJ: 2015-01-15: for now SSL does not clone the context object.
+    // cloning should only be done before the PortCfg is post-configure initialized and opened
     SSL_CTX *sslContext;
 #endif
 
 #endif /*0*/
 
     return b;
 }
 
 #if USE_SSL
-void AnyP::PortCfg::configureSslServerContext()
+void
+AnyP::PortCfg::configureSslServerContext()
 {
     if (cert)
         Ssl::readCertChainAndPrivateKeyFromFiles(signingCert, signPkey, certsToChain, cert, key);
 
     if (!signingCert) {
         char buf[128];
-        fatalf("No valid signing SSL certificate configured for %s_port %s", protocol,  s.ToURL(buf, sizeof(buf)));
+        fatalf("No valid signing SSL certificate configured for %s_port %s", protocol,  s.toUrl(buf, sizeof(buf)));
     }
 
     if (!signPkey)
         debugs(3, DBG_IMPORTANT, "No SSL private key configured for  " <<  protocol << "_port " << s);
 
     Ssl::generateUntrustedCert(untrustedSigningCert, untrustedSignPkey,
                                signingCert, signPkey);
 
     if (!untrustedSigningCert) {
         char buf[128];
-        fatalf("Unable to generate  signing SSL certificate for untrusted sites for %s_port %s", protocol, s.ToURL(buf, sizeof(buf)));
+        fatalf("Unable to generate  signing SSL certificate for untrusted sites for %s_port %s", protocol, s.toUrl(buf, sizeof(buf)));
     }
 
     if (crlfile)
         clientVerifyCrls.reset(Ssl::loadCrl(crlfile, sslContextFlags));
 
     if (clientca) {
