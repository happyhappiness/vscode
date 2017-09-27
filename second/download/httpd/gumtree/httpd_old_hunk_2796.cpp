         */
        l->secure = secureflag;

        /* save away a copy of the client cert list that is presently valid */
        l->client_certs = apr_array_copy_hdr(l->pool, dc->client_certs);

        l->keep = 1;

        if (p) {
            p->next = l;
        }
        else {
            st->connections = l;
