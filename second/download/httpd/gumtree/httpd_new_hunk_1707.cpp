
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
