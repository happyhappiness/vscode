bool
acl_ip_data::DecodeMask(const char *asc, Ip::Address &mask, int ctype)
{
    char junk;
    int a1 = 0;

    /* default is a mask that doesn't change any IP */
    mask.setNoAddr();

    if (!asc || !*asc) {
        return true;
    }

    /* An int mask 128, 32 */
    if ((sscanf(asc, "%d%c", &a1, &junk)==1) &&
            (a1 <= 128) && (a1  >= 0)
       ) {
        return mask.applyMask(a1, ctype);
    }

    /* dotted notation */
    /* assignment returns true if asc contained an IP address as text */
    if ((mask = asc)) {
        /* HACK: IPv4 netmasks don't cleanly map to IPv6 masks. */
        debugs(28, DBG_CRITICAL, "WARNING: Netmasks are deprecated. Please use CIDR masks instead.");
        if (mask.isIPv4()) {
            /* locate what CIDR mask was _probably_ meant to be in its native protocol format. */
            /* this will completely crap out with a security fail-open if the admin is playing mask tricks */
            /* however, thats their fault, and we do warn. see bug 2601 for the effects if we don't do this. */
            unsigned int m = mask.cidr();
            debugs(28, DBG_CRITICAL, "WARNING: IPv4 netmasks are particularly nasty when used to compare IPv6 to IPv4 ranges.");
            debugs(28, DBG_CRITICAL, "WARNING: For now we will assume you meant to write /" << m);
            /* reset the mask completely, and crop to the CIDR boundary back properly. */
            mask.setNoAddr();
            return mask.applyMask(m,AF_INET);
        }
        return true;
    }

    return false;
}