bool
Eui::Eui64::lookupNdp(const Ip::Address &c)
{
#if 0 /* no actual lookup coded yet */

    /* no OS yet supported for NDP protocol lookup */
    debugs(28, DBG_CRITICAL, "ERROR: ARP / MAC / EUI-* operations not supported on this operating system.");

    /*
     * Address was not found on any interface
     */
    debugs(28, 3, HERE << c << " NOT found");
#endif /* 0 */

    clear();
    return false;
}