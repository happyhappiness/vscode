bool
Eui::Eui64::lookupSlaac(const Ip::Address &c)
{
    /* RFC 4291 Link-Local unicast addresses which contain SLAAC - usually trustable. */
    if (c.IsSiteLocal6() && c.IsSlaac() ) {

        // strip the final 64 bits of the address...
        struct in6_addr tmp;
        c.GetInAddr(tmp);
        memcpy(eui, &(tmp.s6_addr[8]), SZ_EUI64_BUF);

        return true;
    }
    return false;
}