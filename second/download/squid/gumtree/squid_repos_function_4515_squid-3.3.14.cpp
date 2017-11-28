bool
acl_ip_data::DecodeMask(const char *asc, Ip::Address &mask, int ctype)
{
    char junk;
    int a1 = 0;

    /* default is a mask that doesn't change any IP */
    mask.SetNoAddr();

    if (!asc || !*asc) {
        return true;
    }

    /* An int mask 128, 32 */
    if ((sscanf(asc, "%d%c", &a1, &junk)==1) &&
            (a1 <= 128) && (a1  >= 0)
       ) {
        return mask.ApplyMask(a1, ctype);
    }

    /* dotted notation */
    /* assignment returns true if asc contained an IP address as text */
    if ((mask = asc)) {
        /* HACK: IPv4 netmasks don't cleanly map to IPv6 masks. */
        debugs(28, DBG_CRITICAL, "WARNING: Netmasks are deprecated. Please use CIDR masks instead.");
        if (mask.IsIPv4()) {
            /* locate what CIDR mask was _probably_ meant to be in its native protocol format. */
            /* this will completely crap out with a security fail-open if the admin is playing mask tricks */
            /* however, thats their fault, and we do warn. see bug 2601 for the effects if we don't do this. */
            unsigned int m = mask.GetCIDR();
            debugs(28, DBG_CRITICAL, "WARNING: IPv4 netmasks are particularly nasty when used to compare IPv6 to IPv4 ranges.");
            debugs(28, DBG_CRITICAL, "WARNING: For now we will assume you meant to write /" << m);
            /* reset the mask completely, and crop to the CIDR boundary back properly. */
            mask.SetNoAddr();
            return mask.ApplyMask(m,AF_INET);
        }
        return true;
    }

    return false;
}