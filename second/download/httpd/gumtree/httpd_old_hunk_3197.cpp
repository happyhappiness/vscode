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
