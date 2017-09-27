                else {
                    /* again, what can we do?  They didn't specify a
                       ServerName, and their DNS isn't working. -djg */
                    char *ipaddr_str;

                    apr_sockaddr_ip_get(&ipaddr_str, s->addrs->host_addr);
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, main_s,
                                 "Failed to resolve server name "
                                 "for %s (check DNS) -- or specify an explicit "
                                 "ServerName",
                                 ipaddr_str);
                    s->server_hostname =
                        apr_pstrdup(p, "bogus_host_without_reverse_dns");
                }
            }
        }
    }

    /* now go through and delete any NameVirtualHosts that didn't have any
     * hosts associated with them.  Lamers.
     */
    for (i = 0; i < IPHASH_TABLE_SIZE; ++i) {
        remove_unused_name_vhosts(main_s, &iphash_table[i]);
    }
    remove_unused_name_vhosts(main_s, &default_list);

#ifdef IPHASH_STATISTICS
    dump_iphash_statistics(main_s);
#endif
    if (ap_exists_config_define("DUMP_VHOSTS")) {
        apr_file_t *thefile = NULL;
        apr_file_open_stdout(&thefile, p);
        dump_vhost_config(thefile);
    }
}


/*****************************************************************************
 * run-time vhost matching functions
 */

/* Lowercase and remove any trailing dot and/or :port from the hostname,
