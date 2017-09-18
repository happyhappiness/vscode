        }
        else if (ssl_err == SSL_ERROR_SSL) {
            /*
             * Log SSL errors
             */
            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                    "SSL error on reading data");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
        }
    }

    return rc;
}

