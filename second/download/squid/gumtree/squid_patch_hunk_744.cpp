     if (s->crlfile)
         storeAppendPrintf(e, " crlfile=%s", s->crlfile);
 
     if (s->dhfile)
         storeAppendPrintf(e, " dhparams=%s", s->dhfile);
 
+    if (s->tls_dh)
+        storeAppendPrintf(e, " tls-dh=%s", s->tls_dh);
+
     if (s->sslflags)
         storeAppendPrintf(e, " sslflags=%s", s->sslflags);
 
     if (s->sslContextSessionId)
         storeAppendPrintf(e, " sslcontext=%s", s->sslContextSessionId);
 
