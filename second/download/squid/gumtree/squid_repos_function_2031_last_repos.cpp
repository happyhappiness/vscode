ipcache_addrs *
ipcacheCheckNumeric(const char *name)
{
    Ip::Address ip;
    /* check if it's already a IP address in text form. */

    /* it may be IPv6-wrapped */
    if (name[0] == '[') {
        char *tmp = xstrdup(&name[1]);
        tmp[strlen(tmp)-1] = '\0';
        if (!(ip = tmp)) {
            delete tmp;
            return NULL;
        }
        delete tmp;
    } else if (!(ip = name))
        return NULL;

    debugs(14, 4, "ipcacheCheckNumeric: HIT_BYPASS for '" << name << "' == " << ip );

    static_addrs.count = 1;

    static_addrs.cur = 0;

    static_addrs.in_addrs[0] = ip;

    static_addrs.bad_mask[0] = FALSE;

    static_addrs.badcount = 0;

    return &static_addrs;
}