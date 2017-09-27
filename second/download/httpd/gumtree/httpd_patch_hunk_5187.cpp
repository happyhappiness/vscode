         SSLSrvConfigRec *sc = mySrvConfig(s);
 
         if (sc && sc->server && sc->server->pks) {
             modssl_pk_server_t *const pks = sc->server->pks;
             int i;
 
-            for (i = 0; (i < SSL_AIDX_MAX) && pks->cert_files[i]; i++) {
-                apr_file_printf(out, "  %s\n", pks->cert_files[i]);
+            for (i = 0; (i < pks->cert_files->nelts) &&
+                        APR_ARRAY_IDX(pks->cert_files, i, const char *);
+                 i++) {
+                apr_file_printf(out, "  %s\n",
+                                APR_ARRAY_IDX(pks->cert_files,
+                                              i, const char *));
             }
         }
 
         s = s->next;
     }
 
