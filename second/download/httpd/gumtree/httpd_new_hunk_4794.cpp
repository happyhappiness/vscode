            an = ssl_util_algotypestr(at);
            if (algoCert & at) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02242)
                             "Init: Multiple %s server certificates not "
                             "allowed", an);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                ssl_die(s);
            }
            algoCert |= at;

            /* Determine the hash key used for this (vhost, algo-type)
             * pair used to index both the mc->tPrivateKey and
             * mc->tPublicCert tables: */
