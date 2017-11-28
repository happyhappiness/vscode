static void
fwdStats(StoreEntry * s)
{
    int i;
    int j;
    storeAppendPrintf(s, "Status");

    for (j = 1; j < MAX_FWD_STATS_IDX; ++j) {
        storeAppendPrintf(s, "\ttry#%d", j);
    }

    storeAppendPrintf(s, "\n");

    for (i = 0; i <= (int) Http::scInvalidHeader; ++i) {
        if (FwdReplyCodes[0][i] == 0)
            continue;

        storeAppendPrintf(s, "%3d", i);

        for (j = 0; j <= MAX_FWD_STATS_IDX; ++j) {
            storeAppendPrintf(s, "\t%d", FwdReplyCodes[j][i]);
        }

        storeAppendPrintf(s, "\n");
    }
}