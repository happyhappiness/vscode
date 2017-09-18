                 * "level optional_no_ca is actually against the idea
                 *  of authentication (but can be used to establish 
                 * SSL test pages, etc.)"
                 * optional_no_ca doesn't appear to work as advertised
                 * in 1.x
                 */
                ssl_log(c->base_server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                        "SSL client authentication failed, "
                        "accepting certificate based on "
                        "\"SSLVerifyClient optional_no_ca\" configuration");
            }
            else {
                const char *error = sslconn->verify_error ?
                    sslconn->verify_error :
                    X509_verify_cert_error_string(verify_result);

                ssl_log(c->base_server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                        "SSL client authentication failed: %s",
                        error ? error : "unknown");

                return ssl_abort(filter, c);
            }
        }

        /*
