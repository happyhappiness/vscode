                 */
                if ((rv = exists_and_readable(szPath, p,
                                              &pkey_mtime)) != APR_SUCCESS ) {
                     ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02243)
                                  "Init: Can't open server private key file "
                                  "%s",szPath);
                     ssl_die(s);
                }

                /*
                 * if the private key is encrypted and SSLPassPhraseDialog
                 * is configured to "builtin" it isn't possible to prompt for
                 * a password after httpd has detached from the tty.
