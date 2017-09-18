        }
        else if (ssl_err == SSL_ERROR_SSL) {
            /*
             * Log SSL errors
             */
            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
            ssl_log(c->base_server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                    "SSL error on reading data");
        }
    }

    return rc;
}

