static int proxy_match_ipaddr(struct dirconn_entry *This, request_rec *r)
{
    int i, ip_addr[4];
    struct in_addr addr, *ip;
    const char *host = proxy_get_host_of_request(r);

    if (host == NULL) {   /* oops! */
       return 0;
    }

    memset(&addr, '\0', sizeof addr);
    memset(ip_addr, '\0', sizeof ip_addr);

    if (4 == sscanf(host, "%d.%d.%d.%d", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3])) {
        for (addr.s_addr = 0, i = 0; i < 4; ++i) {
            /* ap_proxy_is_ipaddr() already confirmed that we have
             * a valid octet in ip_addr[i]
             */
            addr.s_addr |= htonl(ip_addr[i] << (24 - 8 * i));
        }

        if (This->addr.s_addr == (addr.s_addr & This->mask.s_addr)) {
#if DEBUGGING
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "1)IP-Match: %s[%s] <-> ", host, inet_ntoa(addr));
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "%s/", inet_ntoa(This->addr));
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "%s", inet_ntoa(This->mask));
#endif
            return 1;
        }
#if DEBUGGING
        else {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "1)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(addr));
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "%s/", inet_ntoa(This->addr));
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "%s", inet_ntoa(This->mask));
        }
#endif
    }
    else {
        struct apr_sockaddr_t *reqaddr;

        if (apr_sockaddr_info_get(&reqaddr, host, APR_UNSPEC, 0, 0, r->pool)
            != APR_SUCCESS) {
#if DEBUGGING
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
             "2)IP-NoMatch: hostname=%s msg=Host not found", host);
#endif
            return 0;
        }

        /* Try to deal with multiple IP addr's for a host */
        /* FIXME: This needs to be able to deal with IPv6 */
        while (reqaddr) {
            ip = (struct in_addr *) reqaddr->ipaddr_ptr;
            if (This->addr.s_addr == (ip->s_addr & This->mask.s_addr)) {
#if DEBUGGING
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                             "3)IP-Match: %s[%s] <-> ", host, inet_ntoa(*ip));
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                             "%s/", inet_ntoa(This->addr));
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                             "%s", inet_ntoa(This->mask));
#endif
                return 1;
            }
#if DEBUGGING
            else {
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                             "3)IP-NoMatch: %s[%s] <-> ", host, inet_ntoa(*ip));
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                             "%s/", inet_ntoa(This->addr));
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                             "%s", inet_ntoa(This->mask));
            }
#endif
            reqaddr = reqaddr->next;
        }
    }

    return 0;
}