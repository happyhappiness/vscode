            ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                "Cannot resolve host name %s --- ignoring!", host);
            return NULL;
        }
    }

    /* Remember all addresses for the host */

    do {
        sar = apr_pcalloc(p, sizeof(server_addr_rec));
        **paddr = sar;
        *paddr = &sar->next;
        sar->host_addr = my_addr;
        sar->host_port = port;
        sar->virthost = host;
        my_addr = my_addr->next;
    } while (my_addr);

    return NULL;
}


/* parse the <VirtualHost> addresses */
const char *ap_parse_vhost_addrs(apr_pool_t *p,
