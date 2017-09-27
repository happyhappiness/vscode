            ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                "Cannot resolve host name %s --- ignoring!", host);
            return NULL;
        }
    }

    /* XXX Gotta go through *all* addresses for the host name! 
     * Fix apr_sockaddr_info_get() to save them! */

    sar = apr_pcalloc(p, sizeof(server_addr_rec));
    **paddr = sar;
    *paddr = &sar->next;
    sar->host_addr = my_addr;
    sar->host_port = port;
    sar->virthost = host;
    return NULL;
}


/* parse the <VirtualHost> addresses */
const char *ap_parse_vhost_addrs(apr_pool_t *p,
