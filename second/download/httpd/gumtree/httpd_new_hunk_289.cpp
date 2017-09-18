         * Make really sure that when a peer certificate
         * is required we really got one... (be paranoid)
         */
        if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
            !sslconn->client_cert)
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                         "No acceptable peer certificate available");

            return ssl_abort(filter, c);
        }
    }

    return APR_SUCCESS;
