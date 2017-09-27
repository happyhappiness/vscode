         */
        if (c->rwrite == 0) {
            apr_socket_timeout_set(c->aprsock, 0);
            c->connect = tnow;
            c->rwrote = 0;
            c->rwrite = reqlen;
            if (posting)
                c->rwrite += postlen;
        }
        else if (tnow > c->connect + aprtimeout) {
            printf("Send request timed out!\n");
            close_connection(c);
            return;
