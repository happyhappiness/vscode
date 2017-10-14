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