bool
Eui::Eui64::lookup(const Ip::Address &c)
{
    /* try to short-circuit slow OS lookups by using SLAAC data */
    if (lookupSlaac(c))
        return true;

    // find EUI-64 some other way. NDP table lookup?
    return lookupNdp(c);
}