     }
 
     contextMethod = Ssl::contextMethod(version);
     if (!contextMethod)
         fatalf("Unable to compute context method to use");
 
-    if (dhfile)
-        dhParams.reset(Ssl::readDHParams(dhfile));
+    const char *dhParamsFile = dhfile; // backward compatibility for dhparams= configuration
+    safe_free(eecdhCurve); // clear any previous EECDH configuration
+    if (tls_dh && *tls_dh) {
+        eecdhCurve = xstrdup(tls_dh);
+        char *p = strchr(eecdhCurve, ':');
+        if (p) {  // tls-dh=eecdhCurve:dhParamsFile
+            *p = '\0';
+            dhParamsFile = p+1;
+        } else {  // tls-dh=dhParamsFile
+            dhParamsFile = tls_dh;
+            // a NULL eecdhCurve means "do not use EECDH"
+            safe_free(eecdhCurve);
+        }
+    }
+
+    if (dhParamsFile && *dhParamsFile)
+        dhParams.reset(Ssl::readDHParams(dhParamsFile));
 
     if (sslflags)
         sslContextFlags = Ssl::parse_flags(sslflags);
 
     sslOptions = Ssl::parse_options(options);
 
     staticSslContext.reset(sslCreateServerContext(*this));
 
     if (!staticSslContext) {
         char buf[128];
-        fatalf("%s_port %s initialization error", protocol,  s.toUrl(buf, sizeof(buf)));
+        fatalf("%s_port %s initialization error", AnyP::ProtocolType_str[transport.protocol],  s.toUrl(buf, sizeof(buf)));
     }
 }
 #endif
 
