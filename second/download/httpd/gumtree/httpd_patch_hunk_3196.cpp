                  * but we fall through with a chance of success if the key
                  * is not encrypted or can be handled via exec or pipe dialog.
                  * and in the case of fallthrough, pkey_mtime and isatty()
                  * are used to give a better idea as to what failed.
                  */
                 if (pkey_mtime) {
-                    int i;
+                    ssl_asn1_t *asn1 =
+                        ssl_asn1_table_get(mc->tPrivateKey, key_id);
 
-                    for (i=0; i < SSL_AIDX_MAX; i++) {
-                        const char *key_id =
-                            ssl_asn1_table_keyfmt(p, cpVHostID, i);
-                        ssl_asn1_t *asn1 =
-                            ssl_asn1_table_get(mc->tPrivateKey, key_id);
-
-                        if (asn1 && (asn1->source_mtime == pkey_mtime)) {
-                            ap_log_error(APLOG_MARK, APLOG_INFO,
-                                         0, pServ,
-                                         "%s reusing existing "
-                                         "%s private key on restart",
-                                         cpVHostID, ssl_asn1_keystr(i));
-                            return;
-                        }
+                    if (asn1 && (asn1->source_mtime == pkey_mtime)) {
+                        ap_log_error(APLOG_MARK, APLOG_INFO,
+                                     0, pServ, APLOGNO(02244)
+                                     "%s reusing existing "
+                                     "%s private key on restart",
+                                     cpVHostID, ssl_asn1_keystr(i));
+                        using_cache = 1;
+                        break;
                     }
                 }
 
                 cpPassPhraseCur = NULL;
                 ssl_pphrase_server_rec = s; /* to make up for sslc flaw */
 
