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
