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
