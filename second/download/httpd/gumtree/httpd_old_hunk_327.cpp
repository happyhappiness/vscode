     * BUFF code again. This way the data flows twice through the Apache BUFF, of
     * course. But this way the solution doesn't depend on any Apache specifics
     * and is fully transparent to Apache modules.
     *
     * !! BUT ALL THIS IS STILL NOT RE-IMPLEMENTED FOR APACHE 2.0 !!
     */
    if (renegotiate && (r->method_number == M_POST)) {
        ssl_log(r->server, SSL_LOG_ERROR,
                "SSL Re-negotiation in conjunction "
                "with POST method not supported!");

        return HTTP_METHOD_NOT_ALLOWED;
    }

    /*
     * now do the renegotiation if anything was actually reconfigured
