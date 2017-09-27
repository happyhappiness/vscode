                         "Init: Failed to load Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
        }

#ifdef ENGINE_CTRL_CHIL_SET_FORKCHECK
        if (strEQ(mc->szCryptoDevice, "chil")) {
            ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
        }
#endif

        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01889)
                         "Init: Failed to enable Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
