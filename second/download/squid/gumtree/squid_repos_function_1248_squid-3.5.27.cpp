void
AccessLogEntry::getLogClientIp(char *buf, size_t bufsz) const
{
    Ip::Address log_ip;

#if FOLLOW_X_FORWARDED_FOR
    if (Config.onoff.log_uses_indirect_client && request)
        log_ip = request->indirect_client_addr;
    else
#endif
        if (tcpClient != NULL)
            log_ip = tcpClient->remote;
        else
            log_ip = cache.caddr;

    // internally generated requests (and some ICAP) lack client IP
    if (log_ip.isNoAddr()) {
        strncpy(buf, "-", bufsz);
        return;
    }

    // Apply so-called 'privacy masking' to IPv4 clients
    // - localhost IP is always shown in full
    // - IPv4 clients masked with client_netmask
    // - IPv6 clients use 'privacy addressing' instead.

    if (!log_ip.isLocalhost() && log_ip.isIPv4())
        log_ip.applyMask(Config.Addrs.client_netmask);

    log_ip.toStr(buf, bufsz);
}