
                    ic = new_ipaddr_chain(p, s, sar);
                    ic->next = *iphash_table_tail[bucket];
                    *iphash_table_tail[bucket] = ic;
                }
                else if (!add_name_vhost_config(p, main_s, s, sar, ic)) {
                    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING,
                                 0, main_s, "VirtualHost %s:%u overlaps "
                                 "with VirtualHost %s:%u, the first has "
                                 "precedence, perhaps you need a "
                                 "NameVirtualHost directive",
                                 sar->virthost, sar->host_port,
                                 ic->sar->virthost, ic->sar->host_port);
