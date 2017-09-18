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
