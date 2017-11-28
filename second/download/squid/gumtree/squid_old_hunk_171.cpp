
void
fde::DumpStats (StoreEntry *dumpEntry)
{
    int i;
    storeAppendPrintf(dumpEntry, "Active file descriptors:\n");
#ifdef _SQUID_MSWIN_

    storeAppendPrintf(dumpEntry, "%-4s %-10s %-6s %-4s %-7s* %-7s* %-21s %s\n",
                      "File",
                      "Handle",
#else
    storeAppendPrintf(dumpEntry, "%-4s %-6s %-4s %-7s* %-7s* %-21s %s\n",
