static void dump_vhost_config(apr_file_t *f)
{
    ipaddr_chain *ic;
    int i;

    apr_file_printf(f, "VirtualHost configuration:\n");
    for (i = 0; i < IPHASH_TABLE_SIZE; ++i) {
        for (ic = iphash_table[i]; ic; ic = ic->next) {
            dump_a_vhost(f, ic);
        }
    }
    if (default_list) {
        apr_file_printf(f, "wildcard NameVirtualHosts and _default_ servers:\n");
        for (ic = default_list; ic; ic = ic->next) {
            dump_a_vhost(f, ic);
        }
    }
}

/*
 * Two helper functions for ap_fini_vhost_config()
 */
static int add_name_vhost_config(apr_pool_t *p, server_rec *main_s,
                                 server_rec *s, server_addr_rec *sar,
                                 ipaddr_chain *ic)
{
    /* the first time we encounter a NameVirtualHost address
     * ic->server will be NULL, on subsequent encounters
     * ic->names will be non-NULL.
     */
    if (ic->names || ic->server == NULL) {
        name_chain *nc = new_name_chain(p, s, sar);
        nc->next = ic->names;
        ic->names = nc;
        ic->server = s;
        if (sar->host_port != ic->sar->host_port) {
            /* one of the two is a * port, the other isn't */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, main_s,
                         "VirtualHost %s:%u -- mixing * "
                         "ports and non-* ports with "
                         "a NameVirtualHost address is not supported,"
                         " proceeding with undefined results",
                         sar->virthost, sar->host_port);
        }
        return 1;
    }
    else {
        /* IP-based vhosts are handled by the caller */
        return 0;
    }
}

static void remove_unused_name_vhosts(server_rec *main_s, ipaddr_chain **pic)
{
    while (*pic) {
        ipaddr_chain *ic = *pic;

        if (ic->server == NULL) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, main_s,
                         "Either NameVirtualHost %s:%u has no VirtualHosts,"
                         " or there is more than one identical NameVirtualHost line,"
                         " or your VirtualHost declarations do not match the NameVirtualHost line",
                         ic->sar->virthost, ic->sar->host_port);
            *pic = ic->next;
        }
        else {
            pic = &ic->next;
        }
    }
}

/* compile the tables and such we need to do the run-time vhost lookups */
AP_DECLARE(void) ap_fini_vhost_config(apr_pool_t *p, server_rec *main_s)
{
    server_addr_rec *sar;
    int has_default_vhost_addr;
    server_rec *s;
    int i;
    ipaddr_chain **iphash_table_tail[IPHASH_TABLE_SIZE];

    /* terminate the name_vhost list */
    *name_vhost_list_tail = NULL;

    /* Main host first */
    s = main_s;

    if (!s->server_hostname) {
        s->server_hostname = ap_get_local_host(p);
    }

    /* initialize the tails */
    for (i = 0; i < IPHASH_TABLE_SIZE; ++i) {
        iphash_table_tail[i] = &iphash_table[i];
    }

    /* The first things to go into the hash table are the NameVirtualHosts
     * Since name_vhost_list is in the same order that the directives
     * occured in the config file, we'll copy it in that order.
     */
    for (sar = name_vhost_list; sar; sar = sar->next) {
        char inaddr_any[16] = {0}; /* big enough to handle IPv4 or IPv6 */
        unsigned bucket = hash_addr(sar->host_addr);
        ipaddr_chain *ic = new_ipaddr_chain(p, NULL, sar);

        if (memcmp(sar->host_addr->ipaddr_ptr, inaddr_any,
                   sar->host_addr->ipaddr_len)) { /* not IN[6]ADDR_ANY */
            *iphash_table_tail[bucket] = ic;
            iphash_table_tail[bucket] = &ic->next;
        }
        else {
            /* A wildcard NameVirtualHost goes on the default_list so
             * that it can catch incoming requests on any address.
             */
            ic->next = default_list;
            default_list = ic;
        }
        /* Notice that what we've done is insert an ipaddr_chain with
         * both server and names NULL. This fact is used to spot name-
         * based vhosts in add_name_vhost_config().
         */
    }

    /* The next things to go into the hash table are the virtual hosts
     * themselves.  They're listed off of main_s->next in the reverse
     * order they occured in the config file, so we insert them at
     * the iphash_table_tail but don't advance the tail.
     */

    for (s = main_s->next; s; s = s->next) {
        has_default_vhost_addr = 0;
        for (sar = s->addrs; sar; sar = sar->next) {
            ipaddr_chain *ic;
            char inaddr_any[16] = {0}; /* big enough to handle IPv4 or IPv6 */

            if ((sar->host_addr->family == AF_INET &&
                 sar->host_addr->sa.sin.sin_addr.s_addr == DEFAULT_VHOST_ADDR)
                || !memcmp(sar->host_addr->ipaddr_ptr, inaddr_any, sar->host_addr->ipaddr_len)) {
                ic = find_default_server(sar->host_port);
                if (!ic || !add_name_vhost_config(p, main_s, s, sar, ic)) {
                    if (ic && ic->sar->host_port != 0) {
                        ap_log_error(APLOG_MARK, APLOG_WARNING,
                                     0, main_s, "_default_ VirtualHost "
                                     "overlap on port %u, the first has "
                                     "precedence", sar->host_port);
                    }
                    ic = new_ipaddr_chain(p, s, sar);
                    ic->next = default_list;
                    default_list = ic;
                }
                has_default_vhost_addr = 1;
            }
            else {
                /* see if it matches something we've already got */
                ic = find_ipaddr(sar->host_addr);

                if (!ic) {
                    unsigned bucket = hash_addr(sar->host_addr);

                    ic = new_ipaddr_chain(p, s, sar);
                    ic->next = *iphash_table_tail[bucket];
                    *iphash_table_tail[bucket] = ic;
                }
                else if (!add_name_vhost_config(p, main_s, s, sar, ic)) {
                    ap_log_error(APLOG_MARK, APLOG_WARNING,
                                 0, main_s, "VirtualHost %s:%u overlaps "
                                 "with VirtualHost %s:%u, the first has "
                                 "precedence, perhaps you need a "
                                 "NameVirtualHost directive",
                                 sar->virthost, sar->host_port,
                                 ic->sar->virthost, ic->sar->host_port);
                    ic->sar = sar;
                    ic->server = s;
                }
            }
        }

        /* Ok now we want to set up a server_hostname if the user was
         * silly enough to forget one.
         * XXX: This is silly we should just crash and burn.
         */
