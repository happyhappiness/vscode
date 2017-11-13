void ssl_pphrase_Handle(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc;
    server_rec *pServ;
    char *cpVHostID;
    char szPath[MAX_STRING_LEN];
    EVP_PKEY *pPrivateKey;
    ssl_asn1_t *asn1;
    unsigned char *ucp;
    long int length;
    X509 *pX509Cert;
    BOOL bReadable;
    apr_array_header_t *aPassPhrase;
    int nPassPhrase;
    int nPassPhraseCur;
    char *cpPassPhraseCur;
    int nPassPhraseRetry;
    int nPassPhraseDialog;
    int nPassPhraseDialogCur;
    BOOL bPassPhraseDialogOnce;
    char **cpp;
    int i, j;
    ssl_algo_t algoCert, algoKey, at;
    char *an;
    char *cp;
    apr_time_t pkey_mtime = 0;
    int isterm = 1;
    apr_status_t rv;
    /*
     * Start with a fresh pass phrase array
     */
    aPassPhrase       = apr_array_make(p, 2, sizeof(char *));
    nPassPhrase       = 0;
    nPassPhraseDialog = 0;

    /*
     * Walk through all configured servers
     */
    for (pServ = s; pServ != NULL; pServ = pServ->next) {
        sc = mySrvConfig(pServ);

        if (!sc->enabled)
            continue;

        cpVHostID = ssl_util_vhostid(p, pServ);
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, pServ,
                     "Loading certificate & private key of SSL-aware server");

        /*
         * Read in server certificate(s): This is the easy part
         * because this file isn't encrypted in any way.
         */
        if (sc->server->pks->cert_files[0] == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, pServ,
                         "Server should be SSL-aware but has no certificate "
                         "configured [Hint: SSLCertificateFile] (%s:%d)",
                         pServ->defn_name, pServ->defn_line_number);
            ssl_die();
        }
        algoCert = SSL_ALGO_UNKNOWN;
        algoKey  = SSL_ALGO_UNKNOWN;
        for (i = 0, j = 0; i < SSL_AIDX_MAX && sc->server->pks->cert_files[i] != NULL; i++) {

            apr_cpystrn(szPath, sc->server->pks->cert_files[i], sizeof(szPath));
            if ((rv = exists_and_readable(szPath, p, NULL)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                             "Init: Can't open server certificate file %s",
                             szPath);
                ssl_die();
            }
            if ((pX509Cert = SSL_read_X509(szPath, NULL, NULL)) == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                        "Init: Unable to read server certificate from file %s", szPath);
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
                ssl_die();
            }

            /*
             * check algorithm type of certificate and make
             * sure only one certificate per type is used.
             */
            at = ssl_util_algotypeof(pX509Cert, NULL);
            an = ssl_util_algotypestr(at);
            if (algoCert & at) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "Init: Multiple %s server certificates not "
                             "allowed", an);
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
                ssl_die();
            }
            algoCert |= at;

            /*
             * Insert the certificate into global module configuration to let it
             * survive the processing between the 1st Apache API init round (where
             * we operate here) and the 2nd Apache init round (where the
             * certificate is actually used to configure mod_ssl's per-server
             * configuration structures).
             */
            cp = asn1_table_vhost_key(mc, p, cpVHostID, an);
            length = i2d_X509(pX509Cert, NULL);
            ucp = ssl_asn1_table_set(mc->tPublicCert, cp, length);
            (void)i2d_X509(pX509Cert, &ucp); /* 2nd arg increments */

            /*
             * Free the X509 structure
             */
            X509_free(pX509Cert);

            /*
             * Read in the private key: This is the non-trivial part, because the
             * key is typically encrypted, so a pass phrase dialog has to be used
             * to request it from the user (or it has to be alternatively gathered
             * from a dialog program). The important point here is that ISPs
             * usually have hundrets of virtual servers configured and a lot of
             * them use SSL, so really we have to minimize the pass phrase
             * dialogs.
             *
             * The idea is this: When N virtual hosts are configured and all of
             * them use encrypted private keys with different pass phrases, we
             * have no chance and have to pop up N pass phrase dialogs. But
             * usually the admin is clever enough and uses the same pass phrase
             * for more private key files (typically he even uses one single pass
             * phrase for all). When this is the case we can minimize the dialogs
             * by trying to re-use already known/entered pass phrases.
             */
            if (sc->server->pks->key_files[j] != NULL)
                apr_cpystrn(szPath, sc->server->pks->key_files[j++], sizeof(szPath));

            /*
             * Try to read the private key file with the help of
             * the callback function which serves the pass
             * phrases to OpenSSL
             */
            myCtxVarSet(mc,  1, pServ);
            myCtxVarSet(mc,  2, p);
            myCtxVarSet(mc,  3, aPassPhrase);
            myCtxVarSet(mc,  4, &nPassPhraseCur);
            myCtxVarSet(mc,  5, &cpPassPhraseCur);
            myCtxVarSet(mc,  6, cpVHostID);
            myCtxVarSet(mc,  7, an);
            myCtxVarSet(mc,  8, &nPassPhraseDialog);
            myCtxVarSet(mc,  9, &nPassPhraseDialogCur);
            myCtxVarSet(mc, 10, &bPassPhraseDialogOnce);

            nPassPhraseCur        = 0;
            nPassPhraseRetry      = 0;
            nPassPhraseDialogCur  = 0;
            bPassPhraseDialogOnce = TRUE;

            pPrivateKey = NULL;

            for (;;) {
                /*
                 * Try to read the private key file with the help of
                 * the callback function which serves the pass
                 * phrases to OpenSSL
                 */
                if ((rv = exists_and_readable(szPath, p,
                                              &pkey_mtime)) != APR_SUCCESS ) {
                     ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                                  "Init: Can't open server private key file "
                                  "%s",szPath);
                     ssl_die();
                }

                /*
                 * if the private key is encrypted and SSLPassPhraseDialog
                 * is configured to "builtin" it isn't possible to prompt for
                 * a password after httpd has detached from the tty.
                 * in this case if we already have a private key and the
                 * file name/mtime hasn't changed, then reuse the existing key.
                 * we also reuse existing private keys that were encrypted for
                 * exec: and pipe: dialogs to minimize chances to snoop the
                 * password.  that and pipe: dialogs might prompt the user
                 * for password, which on win32 for example could happen 4
                 * times at startup.  twice for each child and twice within
                 * each since apache "restarts itself" on startup.
                 * of course this will not work for the builtin dialog if
                 * the server was started without LoadModule ssl_module
                 * configured, then restarted with it configured.
                 * but we fall through with a chance of success if the key
                 * is not encrypted or can be handled via exec or pipe dialog.
                 * and in the case of fallthrough, pkey_mtime and isatty()
                 * are used to give a better idea as to what failed.
                 */
                if (pkey_mtime) {
                    int i;

                    for (i=0; i < SSL_AIDX_MAX; i++) {
                        const char *key_id =
                            ssl_asn1_table_keyfmt(p, cpVHostID, i);
                        ssl_asn1_t *asn1 =
                            ssl_asn1_table_get(mc->tPrivateKey, key_id);

                        if (asn1 && (asn1->source_mtime == pkey_mtime)) {
                            ap_log_error(APLOG_MARK, APLOG_INFO,
                                         0, pServ,
                                         "%s reusing existing "
                                         "%s private key on restart",
                                         cpVHostID, ssl_asn1_keystr(i));
                            return;
                        }
                    }
                }

                cpPassPhraseCur = NULL;
                ssl_pphrase_server_rec = s; /* to make up for sslc flaw */

                /* Ensure that the error stack is empty; some SSL
                 * functions will fail spuriously if the error stack
                 * is not empty. */
                ERR_clear_error();

                bReadable = ((pPrivateKey = SSL_read_PrivateKey(szPath, NULL,
                            ssl_pphrase_Handle_CB, s)) != NULL ? TRUE : FALSE);

                /*
                 * when the private key file now was readable,
                 * it's fine and we go out of the loop
                 */
                if (bReadable)
                   break;

                /*
                 * when we have more remembered pass phrases
                 * try to reuse these first.
                 */
                if (nPassPhraseCur < nPassPhrase) {
                    nPassPhraseCur++;
                    continue;
                }

                /*
                 * else it's not readable and we have no more
                 * remembered pass phrases. Then this has to mean
                 * that the callback function popped up the dialog
                 * but a wrong pass phrase was entered.  We give the
                 * user (but not the dialog program) a few more
                 * chances...
                 */
#ifndef WIN32
                if ((sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
                       || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE)
#else
                if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE
#endif
                    && cpPassPhraseCur != NULL
                    && nPassPhraseRetry < BUILTIN_DIALOG_RETRIES ) {
                    apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect "
                            "(%d more retr%s permitted).\n",
                            (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry),
                            (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry) == 1 ? "y" : "ies");
                    nPassPhraseRetry++;
                    if (nPassPhraseRetry > BUILTIN_DIALOG_BACKOFF)
                        apr_sleep((nPassPhraseRetry-BUILTIN_DIALOG_BACKOFF)
                                    * 5 * APR_USEC_PER_SEC);
                    continue;
                }
#ifdef WIN32
                if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                                 "Init: SSLPassPhraseDialog builtin is not "
                                 "supported on Win32 (key file "
                                 "%s)", szPath);
                    ssl_die();
                }
#endif /* WIN32 */

                /*
                 * Ok, anything else now means a fatal error.
                 */
                if (cpPassPhraseCur == NULL) {
                    if (nPassPhraseDialogCur && pkey_mtime &&
                        !(isterm = isatty(fileno(stdout)))) /* XXX: apr_isatty() */
                    {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     pServ,
                                     "Init: Unable to read pass phrase "
                                     "[Hint: key introduced or changed "
                                     "before restart?]");
                        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, pServ);
                    }
                    else {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     pServ, "Init: Private key not found");
                        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, pServ);
                    }
                    if (writetty) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                 pServ, "Init: Pass phrase incorrect");
                    ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, pServ);

                    if (writetty) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                ssl_die();
            }

            if (pPrivateKey == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                            "Init: Unable to read server private key from "
                            "file %s [Hint: Perhaps it is in a separate file? "
                            "  See SSLCertificateKeyFile]", szPath);
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
                ssl_die();
            }

            /*
             * check algorithm type of private key and make
             * sure only one private key per type is used.
             */
            at = ssl_util_algotypeof(NULL, pPrivateKey);
            an = ssl_util_algotypestr(at);
            if (algoKey & at) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "Init: Multiple %s server private keys not "
                             "allowed", an);
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
                ssl_die();
            }
            algoKey |= at;

            /*
             * Log the type of reading
             */
            if (nPassPhraseDialogCur == 0) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, pServ,
                             "unencrypted %s private key - pass phrase not "
                             "required", an);
            }
            else {
                if (cpPassPhraseCur != NULL) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 pServ,
                                 "encrypted %s private key - pass phrase "
                                 "requested", an);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 pServ,
                                 "encrypted %s private key - pass phrase"
                                 " reused", an);
                }
            }

            /*
             * Ok, when we have one more pass phrase store it
             */
            if (cpPassPhraseCur != NULL) {
                cpp = (char **)apr_array_push(aPassPhrase);
                *cpp = cpPassPhraseCur;
                nPassPhrase++;
            }

            /*
             * Insert private key into the global module configuration
             * (we convert it to a stand-alone DER byte sequence
             * because the SSL library uses static variables inside a
             * RSA structure which do not survive DSO reloads!)
             */
            cp = asn1_table_vhost_key(mc, p, cpVHostID, an);
            length = i2d_PrivateKey(pPrivateKey, NULL);
            ucp = ssl_asn1_table_set(mc->tPrivateKey, cp, length);
            (void)i2d_PrivateKey(pPrivateKey, &ucp); /* 2nd arg increments */

            if (nPassPhraseDialogCur != 0) {
                /* remember mtime of encrypted keys */
                asn1 = ssl_asn1_table_get(mc->tPrivateKey, cp);
                asn1->source_mtime = pkey_mtime;
            }

            /*
             * Free the private key structure
             */
            EVP_PKEY_free(pPrivateKey);
        }
    }

    /*
     * Let the user know when we're successful.
     */
    if (nPassPhraseDialog > 0) {
        sc = mySrvConfig(s);
        if (writetty) {
            apr_file_printf(writetty, "\n"
                            "OK: Pass Phrase Dialog successful.\n");
        }
    }

    /*
     * Wipe out the used memory from the
     * pass phrase array and then deallocate it
     */
    if (aPassPhrase->nelts) {
        pphrase_array_clear(aPassPhrase);
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "Init: Wiped out the queried pass phrases from memory");
    }

    /* Close the pipes if they were opened
     */
    if (readtty) {
        apr_file_close(readtty);
        apr_file_close(writetty);
        readtty = writetty = NULL;
    }
    return;
}