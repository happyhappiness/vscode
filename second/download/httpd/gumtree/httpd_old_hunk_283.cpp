    }

    if (sslconn->disabled) {
        return DECLINED;
    }

    sslconn->log_level = sc->log_level;

    /*
     * Remember the connection information for
     * later access inside callback functions
     */

    ssl_log(c->base_server, SSL_LOG_INFO,
            "Connection to child %d established "
            "(server %s, client %s)", c->id, sc->vhost_id, 
            c->remote_ip ? c->remote_ip : "unknown");

    /*
     * Seed the Pseudo Random Number Generator (PRNG)
     */
    ssl_rand_seed(c->base_server, c->pool, SSL_RSCTX_CONNECT, "");

