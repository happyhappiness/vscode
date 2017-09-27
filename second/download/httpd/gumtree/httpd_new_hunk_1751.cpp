             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL client authentication failed, "
                          "accepting certificate based on "
                          "\"SSLVerifyClient optional_no_ca\" "
                          "configuration");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);
        }
        else {
            const char *error = sslconn->verify_error ?
                sslconn->verify_error :
                X509_verify_cert_error_string(verify_result);

            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);

            ssl_filter_io_shutdown(filter_ctx, c, 1);
            return APR_ECONNABORTED;
        }
    }

    /*
     * Remember the peer certificate's DN
     */
