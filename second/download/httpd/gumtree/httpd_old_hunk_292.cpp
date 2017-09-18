     */
    ssl_scache_init(base_server, p);

    /*
     *  initialize servers
     */
    ssl_log(base_server, SSL_LOG_INFO,
            "Init: Initializing (virtual) servers for SSL");

    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);
        /*
         * Either now skip this server when SSL is disabled for
         * it or give out some information about what we're
