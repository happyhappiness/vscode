static bool
okToAccept()
{
    static time_t last_warn = 0;

    if (fdNFree() >= RESERVED_FD)
        return true;

    if (last_warn + 15 < squid_curtime) {
        debugs(33, 0, HERE << "WARNING! Your cache is running out of filedescriptors");
        last_warn = squid_curtime;
    }

    return false;
}