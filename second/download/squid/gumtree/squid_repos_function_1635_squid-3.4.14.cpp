static void
statUtilization(StoreEntry * e)
{
    storeAppendPrintf(e, "Cache Utilisation:\n");
    storeAppendPrintf(e, "\n");
    storeAppendPrintf(e, "Last 5 minutes:\n");

    if (NCountHist >= 5)
        statAvgDump(e, 5, 0);
    else
        storeAppendPrintf(e, "(no values recorded yet)\n");

    storeAppendPrintf(e, "\n");

    storeAppendPrintf(e, "Last 15 minutes:\n");

    if (NCountHist >= 15)
        statAvgDump(e, 15, 0);
    else
        storeAppendPrintf(e, "(no values recorded yet)\n");

    storeAppendPrintf(e, "\n");

    storeAppendPrintf(e, "Last hour:\n");

    if (NCountHist >= 60)
        statAvgDump(e, 60, 0);
    else
        storeAppendPrintf(e, "(no values recorded yet)\n");

    storeAppendPrintf(e, "\n");

    storeAppendPrintf(e, "Last 8 hours:\n");

    if (NCountHourHist >= 8)
        statAvgDump(e, 0, 8);
    else
        storeAppendPrintf(e, "(no values recorded yet)\n");

    storeAppendPrintf(e, "\n");

    storeAppendPrintf(e, "Last day:\n");

    if (NCountHourHist >= 24)
        statAvgDump(e, 0, 24);
    else
        storeAppendPrintf(e, "(no values recorded yet)\n");

    storeAppendPrintf(e, "\n");

    storeAppendPrintf(e, "Last 3 days:\n");

    if (NCountHourHist >= 72)
        statAvgDump(e, 0, 72);
    else
        storeAppendPrintf(e, "(no values recorded yet)\n");

    storeAppendPrintf(e, "\n");

    storeAppendPrintf(e, "Totals since cache startup:\n");

    statCountersDump(e);
}