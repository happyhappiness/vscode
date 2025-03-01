void
dnsSubmit(const char *lookup, HLPCB * callback, void *data)
{
    char buf[256];
    static time_t first_warn = 0;
    snprintf(buf, 256, "%s\n", lookup);

    if (dnsservers->stats.queue_size >= (int)dnsservers->childs.n_active && dnsservers->childs.needNew() > 0) {
        helperOpenServers(dnsservers);
    }

    if (dnsservers->stats.queue_size >= (int)(dnsservers->childs.n_running * 2)) {
        if (first_warn == 0)
            first_warn = squid_curtime;

        if (squid_curtime - first_warn > 3 * 60)
            fatal("DNS servers not responding for 3 minutes");

        debugs(34, DBG_IMPORTANT, "dnsSubmit: queue overload, rejecting " << lookup);

        callback(data, (char *)"$fail Temporary network problem, please retry later");

        return;
    }

    first_warn = 0;
    helperSubmit(dnsservers, buf, callback, data);
}