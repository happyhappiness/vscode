                else {
                    /* again, what can we do?  They didn't specify a
                       ServerName, and their DNS isn't working. -djg */
                    char *ipaddr_str;

                    apr_sockaddr_ip_get(&ipaddr_str, s->addrs->host_addr);
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, main_s, APLOGNO(00549)
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

#ifdef IPHASH_STATISTICS
    dump_iphash_statistics(main_s);
#endif
    if (ap_exists_config_define("DUMP_VHOSTS")) {
        apr_file_t *thefile = NULL;
        apr_file_open_stdout(&thefile, p);
        dump_vhost_config(thefile);
    }
}

static int vhost_check_config(apr_pool_t *p, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec *s)
{
    return config_error ? !OK : OK;
}

/*****************************************************************************
 * run-time vhost matching functions
 */

/* Lowercase and remove any trailing dot and/or :port from the hostname,
