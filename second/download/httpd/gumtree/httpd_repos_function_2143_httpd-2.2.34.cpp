static void check_hostalias(request_rec *r)
{
    /*
     * Even if the request has a Host: header containing a port we ignore
     * that port.  We always use the physical port of the socket.  There
     * are a few reasons for this:
     *
     * - the default of 80 or 443 for SSL is easier to handle this way
     * - there is less of a possibility of a security problem
     * - it simplifies the data structure
     * - the client may have no idea that a proxy somewhere along the way
     *   translated the request to another ip:port
     * - except for the addresses from the VirtualHost line, none of the other
     *   names we'll match have ports associated with them
     */
    const char *host = r->hostname;
    apr_port_t port;
    server_rec *s;
    server_rec *last_s;
    name_chain *src;

    last_s = NULL;

    port = r->connection->local_addr->port;

    /* Recall that the name_chain is a list of server_addr_recs, some of
     * whose ports may not match.  Also each server may appear more than
     * once in the chain -- specifically, it will appear once for each
     * address from its VirtualHost line which matched.  We only want to
     * do the full ServerName/ServerAlias comparisons once for each
     * server, fortunately we know that all the VirtualHost addresses for
     * a single server are adjacent to each other.
     */

    for (src = r->connection->vhost_lookup_data; src; src = src->next) {
        server_addr_rec *sar;

        /* We only consider addresses on the name_chain which have a matching
         * port
         */
        sar = src->sar;
        if (sar->host_port != 0 && port != sar->host_port) {
            continue;
        }

        s = src->server;

        /* does it match the virthost from the sar? */
        if (!strcasecmp(host, sar->virthost)) {
            goto found;
        }

        if (s == last_s) {
            /* we've already done ServerName and ServerAlias checks for this
             * vhost
             */
            continue;
        }
        last_s = s;

        if (matches_aliases(s, host)) {
            goto found;
        }
    }
    return;

found:
    /* s is the first matching server, we're done */
    r->server = s;
}