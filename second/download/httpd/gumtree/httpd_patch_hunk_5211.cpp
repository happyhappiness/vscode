 #define BUILTIN_DIALOG_BACKOFF 2
 #define BUILTIN_DIALOG_RETRIES 5
 
 static apr_file_t *writetty = NULL;
 static apr_file_t *readtty = NULL;
 
-/*
- * sslc has a nasty flaw where its
- * PEM_read_bio_PrivateKey does not take a callback arg.
- */
-static server_rec *ssl_pphrase_server_rec = NULL;
-
 int ssl_pphrase_Handle_CB(char *, int, int, void *);
 
 static char *pphrase_array_get(apr_array_header_t *arr, int idx)
 {
     if ((idx < 0) || (idx >= arr->nelts)) {
         return NULL;
     }
 
     return ((char **)arr->elts)[idx];
 }
 
-static void pphrase_array_clear(apr_array_header_t *arr)
-{
-    if (arr->nelts > 0) {
-        memset(arr->elts, 0, arr->elt_size * arr->nelts);
-    }
-    arr->nelts = 0;
-}
-
-/* Abandon all hope, ye who read this code.  Don't believe the name:
- * "passphrase handling" is really a peripheral (if complex) concern;
- * the core purpose of this function to load into memory all
- * configured certs and key from files.  The private key handling in
- * here should be split out into a separate function for improved
- * readability.  The myCtxVarGet abomination can be thrown away with
- * SSLC support, vastly simplifying the code. */
-void ssl_pphrase_Handle(server_rec *s, apr_pool_t *p)
+apr_status_t ssl_load_encrypted_pkey(server_rec *s, apr_pool_t *p, int idx,
+                                     const char *pkey_file,
+                                     apr_array_header_t **pphrases)
 {
     SSLModConfigRec *mc = myModConfig(s);
-    SSLSrvConfigRec *sc;
-    server_rec *pServ;
-    char *cpVHostID;
-    char szPath[MAX_STRING_LEN];
-    EVP_PKEY *pPrivateKey;
+    SSLSrvConfigRec *sc = mySrvConfig(s);
+    const char *key_id = asn1_table_vhost_key(mc, p, sc->vhost_id, idx);
+    EVP_PKEY *pPrivateKey = NULL;
     ssl_asn1_t *asn1;
     unsigned char *ucp;
     long int length;
-    X509 *pX509Cert;
     BOOL bReadable;
-    apr_array_header_t *aPassPhrase;
-    int nPassPhrase;
-    int nPassPhraseCur;
-    char *cpPassPhraseCur;
-    int nPassPhraseRetry;
-    int nPassPhraseDialog;
-    int nPassPhraseDialogCur;
-    BOOL bPassPhraseDialogOnce;
-    char **cpp;
-    int i, j;
-    ssl_algo_t algoCert, algoKey, at;
-    char *an;
+    int nPassPhrase = (*pphrases)->nelts;
+    int nPassPhraseRetry = 0;
     apr_time_t pkey_mtime = 0;
     apr_status_t rv;
+    pphrase_cb_arg_t ppcb_arg;
+
+    if (!pkey_file) {
+         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02573)
+                      "Init: No private key specified for %s", key_id);
+         return ssl_die(s);
+    }
+    else if ((rv = exists_and_readable(pkey_file, p, &pkey_mtime))
+             != APR_SUCCESS ) {
+         ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02574)
+                      "Init: Can't open server private key file %s", pkey_file);
+         return ssl_die(s);
+    }
+
+    ppcb_arg.s                     = s;
+    ppcb_arg.p                     = p;
+    ppcb_arg.aPassPhrase           = *pphrases;
+    ppcb_arg.nPassPhraseCur        = 0;
+    ppcb_arg.cpPassPhraseCur       = NULL;
+    ppcb_arg.nPassPhraseDialog     = 0;
+    ppcb_arg.nPassPhraseDialogCur  = 0;
+    ppcb_arg.bPassPhraseDialogOnce = TRUE;
+    ppcb_arg.key_id                = key_id;
+    ppcb_arg.pkey_file             = pkey_file;
+
     /*
-     * Start with a fresh pass phrase array
-     */
-    aPassPhrase       = apr_array_make(p, 2, sizeof(char *));
-    nPassPhrase       = 0;
-    nPassPhraseDialog = 0;
-
-    /*
-     * Walk through all configured servers
-     */
-    for (pServ = s; pServ != NULL; pServ = pServ->next) {
-        sc = mySrvConfig(pServ);
-        cpVHostID = ssl_util_vhostid(p, pServ);
-        if (!sc->enabled) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, pServ, APLOGNO(02199)
-                         "SSL not enabled on vhost %s, skipping SSL setup",
-                         cpVHostID);
-            continue;
+     * if the private key is encrypted and SSLPassPhraseDialog
+     * is configured to "builtin" it isn't possible to prompt for
+     * a password after httpd has detached from the tty.
+     * in this case if we already have a private key and the
+     * file name/mtime hasn't changed, then reuse the existing key.
+     * we also reuse existing private keys that were encrypted for
+     * exec: and pipe: dialogs to minimize chances to snoop the
+     * password.  that and pipe: dialogs might prompt the user
+     * for password, which on win32 for example could happen 4
+     * times at startup.  twice for each child and twice within
+     * each since apache "restarts itself" on startup.
+     * of course this will not work for the builtin dialog if
+     * the server was started without LoadModule ssl_module
+     * configured, then restarted with it configured.
+     * but we fall through with a chance of success if the key
+     * is not encrypted or can be handled via exec or pipe dialog.
+     * and in the case of fallthrough, pkey_mtime and isatty()
+     * are used to give a better idea as to what failed.
+     */
+    if (pkey_mtime) {
+        ssl_asn1_t *asn1 = ssl_asn1_table_get(mc->tPrivateKey, key_id);
+        if (asn1 && (asn1->source_mtime == pkey_mtime)) {
+            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02575)
+                         "Reusing existing private key from %s on restart",
+                         ppcb_arg.pkey_file);
+            return APR_SUCCESS;
         }
+    }
 
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, pServ, APLOGNO(02200)
-                     "Loading certificate & private key of SSL-aware server '%s'",
-                     cpVHostID);
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02576)
+                 "Attempting to load encrypted (?) private key %s", key_id);
 
+    for (;;) {
         /*
-         * Read in server certificate(s): This is the easy part
-         * because this file isn't encrypted in any way.
+         * Try to read the private key file with the help of
+         * the callback function which serves the pass
+         * phrases to OpenSSL
          */
-        if (sc->server->pks->cert_files[0] == NULL
-            && sc->server->pkcs7 == NULL) {
-            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, pServ, APLOGNO(02240)
-                         "Server should be SSL-aware but has no certificate "
-                         "configured [Hint: SSLCertificateFile] (%s:%d)",
-                         pServ->defn_name, pServ->defn_line_number);
-            ssl_die(pServ);
-        }
-
-        /* Bitmasks for all key algorithms configured for this server;
-         * initialize to zero. */
-        algoCert = SSL_ALGO_UNKNOWN;
-        algoKey  = SSL_ALGO_UNKNOWN;
-
-        /* Iterate through configured certificate files for this
-         * server. */
-        for (i = 0, j = 0; i < SSL_AIDX_MAX
-                 && (sc->server->pks->cert_files[i] != NULL
-                     || sc->server->pkcs7); i++) {
-            const char *key_id;
-            int using_cache = 0;
-
-            if (sc->server->pkcs7) {
-                STACK_OF(X509) *certs = ssl_read_pkcs7(pServ,
-                                                       sc->server->pkcs7);
-                pX509Cert = sk_X509_value(certs, 0);
-                i = SSL_AIDX_MAX;
-            } else {
-                apr_cpystrn(szPath, sc->server->pks->cert_files[i],
-                            sizeof(szPath));
-                if ((rv = exists_and_readable(szPath, p, NULL))
-                    != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02201)
-                                 "Init: Can't open server certificate file %s",
-                                 szPath);
-                    ssl_die(s);
-                }
-                if ((pX509Cert = SSL_read_X509(szPath, NULL, NULL)) == NULL) {
-                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02241)
-                                 "Init: Unable to read server certificate from"
-                                 " file %s", szPath);
-                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                    ssl_die(s);
-                }
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02202)
-                             "Init: Read server certificate from '%s'",
-                             szPath);
-            }
-            /*
-             * check algorithm type of certificate and make
-             * sure only one certificate per type is used.
-             */
-            at = ssl_util_algotypeof(pX509Cert, NULL);
-            an = ssl_util_algotypestr(at);
-            if (algoCert & at) {
-                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02242)
-                             "Init: Multiple %s server certificates not "
-                             "allowed", an);
-                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                ssl_die(s);
-            }
-            algoCert |= at;
-
-            /* Determine the hash key used for this (vhost, algo-type)
-             * pair used to index both the mc->tPrivateKey and
-             * mc->tPublicCert tables: */
-            key_id = asn1_table_vhost_key(mc, p, cpVHostID, an);
 
-            /*
-             * Insert the certificate into global module configuration to let it
-             * survive the processing between the 1st Apache API init round (where
-             * we operate here) and the 2nd Apache init round (where the
-             * certificate is actually used to configure mod_ssl's per-server
-             * configuration structures).
-             */
-            length = i2d_X509(pX509Cert, NULL);
-            ucp = ssl_asn1_table_set(mc->tPublicCert, key_id, length);
-            (void)i2d_X509(pX509Cert, &ucp); /* 2nd arg increments */
+        ppcb_arg.cpPassPhraseCur = NULL;
 
-            /*
-             * Free the X509 structure
-             */
-            X509_free(pX509Cert);
+        /* Ensure that the error stack is empty; some SSL
+         * functions will fail spuriously if the error stack
+         * is not empty. */
+        ERR_clear_error();
+
+        bReadable = ((pPrivateKey = SSL_read_PrivateKey(ppcb_arg.pkey_file,
+                     NULL, ssl_pphrase_Handle_CB, &ppcb_arg)) != NULL ?
+                     TRUE : FALSE);
 
-            /*
-             * Read in the private key: This is the non-trivial part, because the
-             * key is typically encrypted, so a pass phrase dialog has to be used
-             * to request it from the user (or it has to be alternatively gathered
-             * from a dialog program). The important point here is that ISPs
-             * usually have hundrets of virtual servers configured and a lot of
-             * them use SSL, so really we have to minimize the pass phrase
-             * dialogs.
-             *
-             * The idea is this: When N virtual hosts are configured and all of
-             * them use encrypted private keys with different pass phrases, we
-             * have no chance and have to pop up N pass phrase dialogs. But
-             * usually the admin is clever enough and uses the same pass phrase
-             * for more private key files (typically he even uses one single pass
-             * phrase for all). When this is the case we can minimize the dialogs
-             * by trying to re-use already known/entered pass phrases.
-             */
-            if (sc->server->pks->key_files[j] != NULL)
-                apr_cpystrn(szPath, sc->server->pks->key_files[j++], sizeof(szPath));
-
-            /*
-             * Try to read the private key file with the help of
-             * the callback function which serves the pass
-             * phrases to OpenSSL
-             */
-            myCtxVarSet(mc,  1, pServ);
-            myCtxVarSet(mc,  2, p);
-            myCtxVarSet(mc,  3, aPassPhrase);
-            myCtxVarSet(mc,  4, &nPassPhraseCur);
-            myCtxVarSet(mc,  5, &cpPassPhraseCur);
-            myCtxVarSet(mc,  6, cpVHostID);
-            myCtxVarSet(mc,  7, an);
-            myCtxVarSet(mc,  8, &nPassPhraseDialog);
-            myCtxVarSet(mc,  9, &nPassPhraseDialogCur);
-            myCtxVarSet(mc, 10, &bPassPhraseDialogOnce);
-
-            nPassPhraseCur        = 0;
-            nPassPhraseRetry      = 0;
-            nPassPhraseDialogCur  = 0;
-            bPassPhraseDialogOnce = TRUE;
-
-            pPrivateKey = NULL;
-
-            for (;;) {
-                /*
-                 * Try to read the private key file with the help of
-                 * the callback function which serves the pass
-                 * phrases to OpenSSL
-                 */
-                if ((rv = exists_and_readable(szPath, p,
-                                              &pkey_mtime)) != APR_SUCCESS ) {
-                     ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02243)
-                                  "Init: Can't open server private key file "
-                                  "%s",szPath);
-                     ssl_die(s);
-                }
-
-                /*
-                 * if the private key is encrypted and SSLPassPhraseDialog
-                 * is configured to "builtin" it isn't possible to prompt for
-                 * a password after httpd has detached from the tty.
-                 * in this case if we already have a private key and the
-                 * file name/mtime hasn't changed, then reuse the existing key.
-                 * we also reuse existing private keys that were encrypted for
-                 * exec: and pipe: dialogs to minimize chances to snoop the
-                 * password.  that and pipe: dialogs might prompt the user
-                 * for password, which on win32 for example could happen 4
-                 * times at startup.  twice for each child and twice within
-                 * each since apache "restarts itself" on startup.
-                 * of course this will not work for the builtin dialog if
-                 * the server was started without LoadModule ssl_module
-                 * configured, then restarted with it configured.
-                 * but we fall through with a chance of success if the key
-                 * is not encrypted or can be handled via exec or pipe dialog.
-                 * and in the case of fallthrough, pkey_mtime and isatty()
-                 * are used to give a better idea as to what failed.
-                 */
-                if (pkey_mtime) {
-                    ssl_asn1_t *asn1 =
-                        ssl_asn1_table_get(mc->tPrivateKey, key_id);
-
-                    if (asn1 && (asn1->source_mtime == pkey_mtime)) {
-                        ap_log_error(APLOG_MARK, APLOG_INFO,
-                                     0, pServ, APLOGNO(02244)
-                                     "%s reusing existing "
-                                     "%s private key on restart",
-                                     cpVHostID, ssl_asn1_keystr(i));
-                        using_cache = 1;
-                        break;
-                    }
-                }
-
-                cpPassPhraseCur = NULL;
-                ssl_pphrase_server_rec = s; /* to make up for sslc flaw */
+        /*
+         * when the private key file now was readable,
+         * it's fine and we go out of the loop
+         */
+        if (bReadable)
+           break;
 
-                /* Ensure that the error stack is empty; some SSL
-                 * functions will fail spuriously if the error stack
-                 * is not empty. */
-                ERR_clear_error();
-
-                bReadable = ((pPrivateKey = SSL_read_PrivateKey(szPath, NULL,
-                            ssl_pphrase_Handle_CB, s)) != NULL ? TRUE : FALSE);
-
-                /*
-                 * when the private key file now was readable,
-                 * it's fine and we go out of the loop
-                 */
-                if (bReadable)
-                   break;
-
-                /*
-                 * when we have more remembered pass phrases
-                 * try to reuse these first.
-                 */
-                if (nPassPhraseCur < nPassPhrase) {
-                    nPassPhraseCur++;
-                    continue;
-                }
+        /*
+         * when we have more remembered pass phrases
+         * try to reuse these first.
+         */
+        if (ppcb_arg.nPassPhraseCur < nPassPhrase) {
+            ppcb_arg.nPassPhraseCur++;
+            continue;
+        }
 
-                /*
-                 * else it's not readable and we have no more
-                 * remembered pass phrases. Then this has to mean
-                 * that the callback function popped up the dialog
-                 * but a wrong pass phrase was entered.  We give the
-                 * user (but not the dialog program) a few more
-                 * chances...
-                 */
+        /*
+         * else it's not readable and we have no more
+         * remembered pass phrases. Then this has to mean
+         * that the callback function popped up the dialog
+         * but a wrong pass phrase was entered.  We give the
+         * user (but not the dialog program) a few more
+         * chances...
+         */
 #ifndef WIN32
-                if ((sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
-                       || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE)
+        if ((sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
+             || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE)
 #else
-                if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE
+        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE
 #endif
-                    && cpPassPhraseCur != NULL
-                    && nPassPhraseRetry < BUILTIN_DIALOG_RETRIES ) {
-                    apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect "
-                            "(%d more retr%s permitted).\n",
-                            (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry),
-                            (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry) == 1 ? "y" : "ies");
-                    nPassPhraseRetry++;
-                    if (nPassPhraseRetry > BUILTIN_DIALOG_BACKOFF)
-                        apr_sleep((nPassPhraseRetry-BUILTIN_DIALOG_BACKOFF)
-                                    * 5 * APR_USEC_PER_SEC);
-                    continue;
-                }
+            && ppcb_arg.cpPassPhraseCur != NULL
+            && nPassPhraseRetry < BUILTIN_DIALOG_RETRIES ) {
+            apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect "
+                    "(%d more retr%s permitted).\n",
+                    (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry),
+                    (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry) == 1 ? "y" : "ies");
+            nPassPhraseRetry++;
+            if (nPassPhraseRetry > BUILTIN_DIALOG_BACKOFF)
+                apr_sleep((nPassPhraseRetry-BUILTIN_DIALOG_BACKOFF)
+                            * 5 * APR_USEC_PER_SEC);
+            continue;
+        }
 #ifdef WIN32
-                if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN) {
-                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02245)
-                                 "Init: SSLPassPhraseDialog builtin is not "
-                                 "supported on Win32 (key file "
-                                 "%s)", szPath);
-                    ssl_die(s);
-                }
+        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN) {
+            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02577)
+                         "Init: SSLPassPhraseDialog builtin is not "
+                         "supported on Win32 (key file "
+                         "%s)", ppcb_arg.pkey_file);
+            return ssl_die(s);
+        }
 #endif /* WIN32 */
 
-                /*
-                 * Ok, anything else now means a fatal error.
-                 */
-                if (cpPassPhraseCur == NULL) {
-                    if (nPassPhraseDialogCur && pkey_mtime &&
-                        !isatty(fileno(stdout))) /* XXX: apr_isatty() */
-                    {
-                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
-                                     pServ, APLOGNO(02246)
-                                     "Init: Unable to read pass phrase "
-                                     "[Hint: key introduced or changed "
-                                     "before restart?]");
-                        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
-                    }
-                    else {
-                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
-                                     pServ, APLOGNO(02203) "Init: Private key not found");
-                        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
-                    }
-                    if (writetty) {
-                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
-                        apr_file_printf(writetty, "**Stopped\n");
-                    }
-                }
-                else {
-                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, pServ, APLOGNO(02204)
-                                 "Init: Pass phrase incorrect for key of %s",
-                                 cpVHostID);
-                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, pServ);
-
-                    if (writetty) {
-                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
-                        apr_file_printf(writetty, "**Stopped\n");
-                    }
-                }
-                ssl_die(pServ);
-            }
-
-            /* If a cached private key was found, nothing more to do
-             * here; loop through to the next configured cert for this
-             * vhost. */
-            if (using_cache)
-                continue;
-
-            if (pPrivateKey == NULL) {
-                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02247)
-                            "Init: Unable to read server private key from "
-                            "file %s [Hint: Perhaps it is in a separate file? "
-                            "  See SSLCertificateKeyFile]", szPath);
-                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                ssl_die(s);
-            }
-
-            /*
-             * check algorithm type of private key and make
-             * sure only one private key per type is used.
-             */
-            at = ssl_util_algotypeof(NULL, pPrivateKey);
-            an = ssl_util_algotypestr(at);
-            if (algoKey & at) {
-                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02248)
-                             "Init: Multiple %s server private keys not "
-                             "allowed", an);
-                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                ssl_die(s);
-            }
-            algoKey |= at;
-
-            /*
-             * Log the type of reading
-             */
-            if (nPassPhraseDialogCur == 0) {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, pServ, APLOGNO(02249)
-                             "unencrypted %s private key - pass phrase not "
-                             "required", an);
+        /*
+         * Ok, anything else now means a fatal error.
+         */
+        if (ppcb_arg.cpPassPhraseCur == NULL) {
+            if (ppcb_arg.nPassPhraseDialogCur && pkey_mtime &&
+                !isatty(fileno(stdout))) /* XXX: apr_isatty() */
+            {
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
+                             s, APLOGNO(02578)
+                             "Init: Unable to read pass phrase "
+                             "[Hint: key introduced or changed "
+                             "before restart?]");
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
             }
             else {
-                if (cpPassPhraseCur != NULL) {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
-                                 pServ, APLOGNO(02250)
-                                 "encrypted %s private key - pass phrase "
-                                 "requested", an);
-                }
-                else {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
-                                 pServ, APLOGNO(02251)
-                                 "encrypted %s private key - pass phrase"
-                                 " reused", an);
-                }
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
+                             s, APLOGNO(02579) "Init: Private key not found");
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+            }
+            if (writetty) {
+                apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
+                apr_file_printf(writetty, "**Stopped\n");
             }
-
-            /*
-             * Ok, when we have one more pass phrase store it
-             */
-            if (cpPassPhraseCur != NULL) {
-                cpp = (char **)apr_array_push(aPassPhrase);
-                *cpp = cpPassPhraseCur;
-                nPassPhrase++;
+        }
+        else {
+            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02580)
+                         "Init: Pass phrase incorrect for key %s",
+                         key_id);
+            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
+
+            if (writetty) {
+                apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
+                apr_file_printf(writetty, "**Stopped\n");
             }
+        }
+        return ssl_die(s);
+    }
 
-            /*
-             * Insert private key into the global module configuration
-             * (we convert it to a stand-alone DER byte sequence
-             * because the SSL library uses static variables inside a
-             * RSA structure which do not survive DSO reloads!)
-             */
-            length = i2d_PrivateKey(pPrivateKey, NULL);
-            ucp = ssl_asn1_table_set(mc->tPrivateKey, key_id, length);
-            (void)i2d_PrivateKey(pPrivateKey, &ucp); /* 2nd arg increments */
-
-            if (nPassPhraseDialogCur != 0) {
-                /* remember mtime of encrypted keys */
-                asn1 = ssl_asn1_table_get(mc->tPrivateKey, key_id);
-                asn1->source_mtime = pkey_mtime;
-            }
+    if (pPrivateKey == NULL) {
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02581)
+                     "Init: Unable to read server private key from file %s",
+                     ppcb_arg.pkey_file);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
+        return ssl_die(s);
+    }
 
-            /*
-             * Free the private key structure
-             */
-            EVP_PKEY_free(pPrivateKey);
+    /*
+     * Log the type of reading
+     */
+    if (ppcb_arg.nPassPhraseDialogCur == 0) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02582)
+                     "unencrypted %s private key - pass phrase not "
+                     "required", key_id);
+    }
+    else {
+        if (ppcb_arg.cpPassPhraseCur != NULL) {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
+                         s, APLOGNO(02583)
+                         "encrypted %s private key - pass phrase "
+                         "requested", key_id);
         }
+        else {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
+                         s, APLOGNO(02584)
+                         "encrypted %s private key - pass phrase"
+                         " reused", key_id);
+        }
+    }
+
+    /*
+     * Ok, when we have one more pass phrase store it
+     */
+    if (ppcb_arg.cpPassPhraseCur != NULL) {
+        *(const char **)apr_array_push(ppcb_arg.aPassPhrase) =
+            ppcb_arg.cpPassPhraseCur;
+        nPassPhrase++;
     }
 
     /*
+     * Insert private key into the global module configuration
+     * (we convert it to a stand-alone DER byte sequence
+     * because the SSL library uses static variables inside a
+     * RSA structure which do not survive DSO reloads!)
+     */
+    length = i2d_PrivateKey(pPrivateKey, NULL);
+    ucp = ssl_asn1_table_set(mc->tPrivateKey, key_id, length);
+    (void)i2d_PrivateKey(pPrivateKey, &ucp); /* 2nd arg increments */
+
+    if (ppcb_arg.nPassPhraseDialogCur != 0) {
+        /* remember mtime of encrypted keys */
+        asn1 = ssl_asn1_table_get(mc->tPrivateKey, key_id);
+        asn1->source_mtime = pkey_mtime;
+    }
+
+    /*
+     * Free the private key structure
+     */
+    EVP_PKEY_free(pPrivateKey);
+
+    /*
      * Let the user know when we're successful.
      */
-    if (nPassPhraseDialog > 0) {
+    if ((ppcb_arg.nPassPhraseDialog > 0) &&
+        (ppcb_arg.cpPassPhraseCur != NULL)) {
         if (writetty) {
             apr_file_printf(writetty, "\n"
                             "OK: Pass Phrase Dialog successful.\n");
         }
     }
 
-    /*
-     * Wipe out the used memory from the
-     * pass phrase array and then deallocate it
-     */
-    if (aPassPhrase->nelts) {
-        pphrase_array_clear(aPassPhrase);
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02205)
-                     "Init: Wiped out the queried pass phrases from memory");
-    }
-
     /* Close the pipes if they were opened
      */
     if (readtty) {
         apr_file_close(readtty);
         apr_file_close(writetty);
         readtty = writetty = NULL;
     }
-    return;
+
+    return APR_SUCCESS;
 }
 
 static apr_status_t ssl_pipe_child_create(apr_pool_t *p, const char *progname)
 {
     /* Child process code for 'ErrorLog "|..."';
      * may want a common framework for this, since I expect it will
