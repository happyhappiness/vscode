            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "Init: Failed to enable Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
            ssl_die();
        }
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, 
                     "Init: loaded Crypto Device API `%s'", 
                     mc->szCryptoDevice);

        ENGINE_free(e);
    }
}
#endif

