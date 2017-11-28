bool
Eui::Eui64::lookupSlaac(const Ip::Address &c)
{
    /* RFC 4291 Link-Local unicast addresses which contain SLAAC - usually trustable. */
    if (c.isSiteLocal6() && c.isSiteLocalAuto()) {

        // strip the final 64 bits of the address...
        struct in6_addr tmp;
        c.getInAddr(tmp);
        memcpy(eui, &(tmp.s6_addr[8]), SZ_EUI64_BUF);
        debugs(28, 4, "id=" << (void*)this << " SLAAC decoded " << c);
        return true;
    }

    debugs(28, 4, "id=" << (void*)this << " SLAAC fail on " << c << " SL-6="
           << (c.isSiteLocal6()?'T':'F') << " AAC-6=" << (c.isSiteLocalAuto()?'T':'F'));
    return false;
}