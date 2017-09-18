                        apr_sleep((nPassPhraseRetry-BUILTIN_DIALOG_BACKOFF)
                                    * 5 * APR_USEC_PER_SEC);
                    continue;
                }
#ifdef WIN32
                if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN) {
                    ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                            "Init: PassPhraseDialog BuiltIn not supported in server private key from file %s", szPath);
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
                        ssl_log(pServ, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                                "Init: Unable read passphrase "
                                "[Hint: key introduced or changed before restart?]");
                    }
                    else {
                        ssl_log(pServ, SSL_LOG_ERROR|SSL_ADD_SSLERR, "Init: Private key not found");
                    }
                    if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
                          || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                else {
                    ssl_log(pServ, SSL_LOG_ERROR|SSL_ADD_SSLERR, "Init: Pass phrase incorrect");
                    if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
                          || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                ssl_die();
            }

            if (pPrivateKey == NULL) {
                ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                        "Init: Unable to read server private key from file %s [Hint: Perhaps it is in a separate file?  See SSLCertificateKeyFile]", szPath);
                ssl_die();
            }

            /*
             * check algorithm type of private key and make
             * sure only one private key per type is used.
             */
            at = ssl_util_algotypeof(NULL, pPrivateKey);
            an = ssl_util_algotypestr(at);
            if (algoKey & at) {
                ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                        "Init: Multiple %s server private keys not allowed", an);
                ssl_die();
            }
            algoKey |= at;

            /*
             * Log the type of reading
             */
            if (nPassPhraseDialogCur == 0) {
                ssl_log(pServ, SSL_LOG_TRACE|SSL_INIT, 
                        "unencrypted %s private key - pass phrase not required", 
                        an);
            }
            else {
                if (cpPassPhraseCur != NULL) {
                    ssl_log(pServ, SSL_LOG_TRACE|SSL_INIT, 
                            "encrypted %s private key - pass phrase requested", 
                            an);
                }
                else {
                    ssl_log(pServ, SSL_LOG_TRACE|SSL_INIT, 
                            "encrypted %s private key - pass phrase reused", 
                            an);
                }
            }

            /*
             * Ok, when we have one more pass phrase store it
             */
