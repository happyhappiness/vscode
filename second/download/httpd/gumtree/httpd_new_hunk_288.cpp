                 * "level optional_no_ca is actually against the idea
                 *  of authentication (but can be used to establish 
                 * SSL test pages, etc.)"
                 * optional_no_ca doesn't appear to work as advertised
                 * in 1.x
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             c->base_server,
                             "SSL client authentication failed, "
                             "accepting certificate based on "
                             "\"SSLVerifyClient optional_no_ca\" "
                             "configuration");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
            }
            else {
                const char *error = sslconn->verify_error ?
                    sslconn->verify_error :
                    X509_verify_cert_error_string(verify_result);

                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             c->base_server,
                             "SSL client authentication failed: %s",
                             error ? error : "unknown");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);

                return ssl_abort(filter, c);
            }
        }

        /*
