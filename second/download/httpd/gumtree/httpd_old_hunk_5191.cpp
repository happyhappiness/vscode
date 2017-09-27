         * configuring.
         */

        /*
         * Read the server certificate and key
         */
        ssl_init_ConfigureServer(s, p, ptemp, sc);
    }

    /*
     * Configuration consistency checks
     */
    ssl_init_CheckServers(base_server, ptemp);

    /*
     *  Announce mod_ssl and SSL library in HTTP Server field
     *  as ``mod_ssl/X.X.X OpenSSL/X.X.X''
     */
    ssl_add_version_components(p, base_server);
