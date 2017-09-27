                 */
                if (cpPassPhraseCur == NULL) {
                    if (nPassPhraseDialogCur && pkey_mtime &&
                        !isatty(fileno(stdout))) /* XXX: apr_isatty() */
                    {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     pServ, APLOGNO(02246)
                                     "Init: Unable to read pass phrase "
                                     "[Hint: key introduced or changed "
                                     "before restart?]");
                        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
                    }
                    else {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     pServ, APLOGNO(02203) "Init: Private key not found");
                        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
                    }
                    if (writetty) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, pServ, APLOGNO(02204)
                                 "Init: Pass phrase incorrect for key of %s",
                                 cpVHostID);
                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, pServ);

                    if (writetty) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                ssl_die();
            }

            /* If a cached private key was found, nothing more to do
             * here; loop through to the next configured cert for this
             * vhost. */
            if (using_cache)
                continue;

            if (pPrivateKey == NULL) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02247)
                            "Init: Unable to read server private key from "
                            "file %s [Hint: Perhaps it is in a separate file? "
                            "  See SSLCertificateKeyFile]", szPath);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                ssl_die();
            }

            /*
             * check algorithm type of private key and make
             * sure only one private key per type is used.
             */
            at = ssl_util_algotypeof(NULL, pPrivateKey);
            an = ssl_util_algotypestr(at);
            if (algoKey & at) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02248)
                             "Init: Multiple %s server private keys not "
                             "allowed", an);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                ssl_die();
            }
            algoKey |= at;

            /*
             * Log the type of reading
             */
            if (nPassPhraseDialogCur == 0) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, pServ, APLOGNO(02249)
                             "unencrypted %s private key - pass phrase not "
                             "required", an);
            }
            else {
                if (cpPassPhraseCur != NULL) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 pServ, APLOGNO(02250)
                                 "encrypted %s private key - pass phrase "
                                 "requested", an);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 pServ, APLOGNO(02251)
                                 "encrypted %s private key - pass phrase"
                                 " reused", an);
                }
            }

            /*
