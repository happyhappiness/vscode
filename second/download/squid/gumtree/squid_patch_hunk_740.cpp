         s->generateHostCertificates = true;
     } else if (strcmp(token, "generate-host-certificates=off") == 0) {
         s->generateHostCertificates = false;
     } else if (strncmp(token, "dynamic_cert_mem_cache_size=", 28) == 0) {
         parseBytesOptionValue(&s->dynamicCertMemCacheSize, B_BYTES_STR, token + 28);
 #endif
+    } else if (strcmp(token, "ftp-track-dirs") == 0) {
+        s->ftp_track_dirs = true;
     } else {
-        debugs(3, DBG_CRITICAL, "FATAL: Unknown http(s)_port option '" << token << "'.");
+        debugs(3, DBG_CRITICAL, "FATAL: Unknown " << cfg_directive << " option '" << token << "'.");
         self_destruct();
     }
 }
 
 void
 add_http_port(char *portspec)
 {
-    AnyP::PortCfg *s = new AnyP::PortCfg("http_port");
+    AnyP::PortCfgPointer s = new AnyP::PortCfg();
+    s->transport = parsePortProtocol(SBuf("HTTP"));
     parsePortSpecification(s, portspec);
     // we may need to merge better if the above returns a list with clones
     assert(s->next == NULL);
-    s->next = cbdataReference(Config.Sockaddr.http);
-    cbdataReferenceDone(Config.Sockaddr.http);
-    Config.Sockaddr.http = cbdataReference(s);
+    s->next = HttpPortList;
+    HttpPortList = s;
 }
 
 static void
-parsePortCfg(AnyP::PortCfg ** head, const char *optionName)
+parsePortCfg(AnyP::PortCfgPointer *head, const char *optionName)
 {
-    const char *protocol = NULL;
+    SBuf protoName;
     if (strcmp(optionName, "http_port") == 0 ||
             strcmp(optionName, "ascii_port") == 0)
-        protocol = "http";
+        protoName = "HTTP";
     else if (strcmp(optionName, "https_port") == 0)
-        protocol = "https";
-    if (!protocol) {
+        protoName = "HTTPS";
+    else if (strcmp(optionName, "ftp_port") == 0)
+        protoName = "FTP";
+    if (protoName.isEmpty()) {
         self_destruct();
         return;
     }
 
-    char *token = strtok(NULL, w_space);
+    char *token = ConfigParser::NextToken();
 
     if (!token) {
         self_destruct();
         return;
     }
 
-    AnyP::PortCfg *s = new AnyP::PortCfg(protocol);
+    AnyP::PortCfgPointer s = new AnyP::PortCfg();
+    s->transport = parsePortProtocol(protoName); // default; protocol=... overwrites
     parsePortSpecification(s, token);
 
     /* parse options ... */
-    while ((token = strtok(NULL, w_space))) {
+    while ((token = ConfigParser::NextToken())) {
         parse_port_option(s, token);
     }
 
-#if USE_SSL
-    if (strcmp(protocol, "https") == 0) {
+    if (s->transport.protocol == AnyP::PROTO_HTTPS) {
+#if USE_OPENSSL
         /* ssl-bump on https_port configuration requires either tproxy or intercept, and vice versa */
         const bool hijacked = s->flags.isIntercepted();
         if (s->flags.tunnelSslBumping && !hijacked) {
             debugs(3, DBG_CRITICAL, "FATAL: ssl-bump on https_port requires tproxy/intercept which is missing.");
             self_destruct();
         }
         if (hijacked && !s->flags.tunnelSslBumping) {
             debugs(3, DBG_CRITICAL, "FATAL: tproxy/intercept on https_port requires ssl-bump which is missing.");
             self_destruct();
         }
-    }
 #endif
+        if (s->flags.proxySurrogate) {
+            debugs(3,DBG_CRITICAL, "FATAL: https_port: require-proxy-header option is not supported on HTTPS ports.");
+            self_destruct();
+        }
+    } else if (protoName.cmp("FTP") == 0) {
+        /* ftp_port does not support ssl-bump */
+        if (s->flags.tunnelSslBumping) {
+            debugs(3, DBG_CRITICAL, "FATAL: ssl-bump is not supported for ftp_port.");
+            self_destruct();
+        }
+        if (s->flags.proxySurrogate) {
+            // Passive FTP data channel does not work without deep protocol inspection in the frontend.
+            debugs(3,DBG_CRITICAL, "FATAL: require-proxy-header option is not supported on ftp_port.");
+            self_destruct();
+        }
+    }
 
     if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && s->s.isAnyAddr()) {
         // clone the port options from *s to *(s->next)
-        s->next = cbdataReference(s->clone());
+        s->next = s->clone();
         s->next->s.setIPv4();
-        debugs(3, 3, protocol << "_port: clone wildcard address for split-stack: " << s->s << " and " << s->next->s);
+        debugs(3, 3, AnyP::UriScheme(s->transport.protocol).c_str() << "_port: clone wildcard address for split-stack: " << s->s << " and " << s->next->s);
     }
 
-    while (*head)
-        head = &(*head)->next;
+    while (*head != NULL)
+        head = &((*head)->next);
 
-    *head = cbdataReference(s);
+    *head = s;
 }
 
 static void
-dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfg * s)
+dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfgPointer &s)
 {
     char buf[MAX_IPSTRLEN];
 
     storeAppendPrintf(e, "%s %s",
                       n,
                       s->s.toUrl(buf,MAX_IPSTRLEN));
