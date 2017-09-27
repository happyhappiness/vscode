#ifdef WIN32
                if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02245)
                                 "Init: SSLPassPhraseDialog builtin is not "
                                 "supported on Win32 (key file "
                                 "%s)", szPath);
                    ssl_die();
                }
#endif /* WIN32 */

                /*
                 * Ok, anything else now means a fatal error.
                 */
