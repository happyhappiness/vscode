        return;

    x = Squid_MaxFD - 20 - min(25, Squid_MaxFD / 16);

    if (newReserve > x) {
        /* perhaps this should be fatal()? -DW */
        debugs(51, 0, "WARNING: This machine has a serious shortage of filedescriptors.");
        newReserve = x;
    }

    if (Squid_MaxFD - newReserve < min(256, Squid_MaxFD / 2))
        fatalf("Too few filedescriptors available in the system (%d usable of %d).\n", Squid_MaxFD - newReserve, Squid_MaxFD);

    debugs(51, 0, "Reserved FD adjusted from " << RESERVED_FD << " to " << newReserve << " due to failures");
    RESERVED_FD = newReserve;
}
