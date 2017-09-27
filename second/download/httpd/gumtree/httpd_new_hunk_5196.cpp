                                           mctx->auth.ca_cert_path))
        {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01895)
                    "Unable to configure verify locations "
                    "for client authentication");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
        }

        if (mctx->pks && (mctx->pks->ca_name_file || mctx->pks->ca_name_path)) {
            ca_list = ssl_init_FindCAList(s, ptemp,
                                          mctx->pks->ca_name_file,
                                          mctx->pks->ca_name_path);
