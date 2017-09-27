 
     /*
      * Filter program
      */
     else if (sc->server->pphrase_dialog_type == SSL_PPTYPE_FILTER) {
         const char *cmd = sc->server->pphrase_dialog_path;
-        const char **argv = apr_palloc(ppcb_arg->p, sizeof(char *) * 3);
+        const char **argv = apr_palloc(ppcb_arg->p, sizeof(char *) * 4);
+        const char *idx = ap_strrchr_c(ppcb_arg->key_id, ':') + 1;
         char *result;
+        int i;
 
         ap_log_error(APLOG_MARK, APLOG_INFO, 0, ppcb_arg->s, APLOGNO(01969)
                      "Init: Requesting pass phrase from dialog filter "
                      "program (%s)", cmd);
 
         argv[0] = cmd;
-        argv[1] = ppcb_arg->key_id;
-        argv[2] = NULL;
+        argv[1] = apr_pstrndup(ppcb_arg->p, ppcb_arg->key_id,
+                               idx-1 - ppcb_arg->key_id);
+        if ((i = atoi(idx)) < CERTKEYS_IDX_MAX+1) {
+            /*
+             * For compatibility with existing 2.4.x configurations, use
+             * "RSA", "DSA" and "ECC" strings for the first two/three keys
+             */
+            argv[2] = key_types[i];
+        } else {
+            /* Four and above: use the integer index */
+            argv[2] = apr_pstrdup(ppcb_arg->p, idx);
+        }
+        argv[3] = NULL;
 
         result = ssl_util_readfilter(ppcb_arg->s, ppcb_arg->p, cmd, argv);
         apr_cpystrn(buf, result, bufsize);
         len = strlen(buf);
     }
 
