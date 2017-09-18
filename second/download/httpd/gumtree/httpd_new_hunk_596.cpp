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
