void
fdAdjustReserved(void)
{
    int newReserve;
    int x;
    static time_t last = 0;
    /*
     * don't update too frequently
     */

    if (last + 5 > squid_curtime)
        return;

    /*
     * Calculate a new reserve, based on current usage and a small extra
     */
    newReserve = Squid_MaxFD - Number_FD + min(25, Squid_MaxFD / 16);

    if (newReserve <= RESERVED_FD)
        return;

    x = Squid_MaxFD - 20 - min(25, Squid_MaxFD / 16);

    if (newReserve > x) {
        /* perhaps this should be fatal()? -DW */
        debugs(51, DBG_CRITICAL, "WARNING: This machine has a serious shortage of filedescriptors.");
        newReserve = x;
    }

    if (Squid_MaxFD - newReserve < min(256, Squid_MaxFD / 2))
        fatalf("Too few filedescriptors available in the system (%d usable of %d).\n", Squid_MaxFD - newReserve, Squid_MaxFD);

    debugs(51, DBG_CRITICAL, "Reserved FD adjusted from " << RESERVED_FD << " to " << newReserve <<
           " due to failures (" << (Squid_MaxFD - newReserve) << "/" << Squid_MaxFD << " file descriptors available)");
    RESERVED_FD = newReserve;
}