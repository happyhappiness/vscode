            for (;;) {
                /*
                 * Try to read the private key file with the help of
                 * the callback function which serves the pass
                 * phrases to OpenSSL
                 */
                if ( exists_and_readable(szPath, p, &pkey_mtime) != APR_SUCCESS ) {
                     ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                         "Init: Can't open server private key file %s",szPath);
                     ssl_die();
                }

                /*
                 * if the private key is encrypted and SSLPassPhraseDialog
                 * is configured to "builtin" it isn't possible to prompt for
