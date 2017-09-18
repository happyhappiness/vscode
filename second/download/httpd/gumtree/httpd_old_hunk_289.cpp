         * Make really sure that when a peer certificate
         * is required we really got one... (be paranoid)
         */
        if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
            !sslconn->client_cert)
        {
            ssl_log(c->base_server, SSL_LOG_ERROR,
                    "No acceptable peer certificate available");

            return ssl_abort(filter, c);
        }
    }

    return APR_SUCCESS;
