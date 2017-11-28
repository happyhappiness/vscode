void
fde::dumpStats (StoreEntry &dumpEntry, int fdNumber)
{
    if (!flags.open)
        return;

#if _SQUID_MSWIN_

    storeAppendPrintf(&dumpEntry, "%4d 0x%-8lX %-6.6s %4d %7" PRId64 "%c %7" PRId64 "%c %-21s %s\n",
                      fdNumber,
                      win32.handle,
#else
    storeAppendPrintf(&dumpEntry, "%4d %-6.6s %4d %7" PRId64 "%c %7" PRId64 "%c %-21s %s\n",
