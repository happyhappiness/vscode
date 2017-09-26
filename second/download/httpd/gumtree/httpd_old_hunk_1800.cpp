
#endif /* USE_SSL */

static void write_request(struct connection * c)
{
    do {
        apr_time_t tnow = apr_time_now();
        apr_size_t l = c->rwrite;
        apr_status_t e = APR_SUCCESS; /* prevent gcc warning */

        /*
         * First time round ?
         */
        if (c->rwrite == 0) {
            apr_socket_timeout_set(c->aprsock, 0);
            c->connect = tnow;
            c->rwrite = reqlen;
            c->rwrote = 0;
            if (posting)
                c->rwrite += postlen;
        }
        else if (tnow > c->connect + aprtimeout) {
            printf("Send request timed out!\n");
            close_connection(c);
