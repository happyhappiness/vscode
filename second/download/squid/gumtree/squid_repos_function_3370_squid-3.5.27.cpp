void
PconnPool::dumpHist(StoreEntry * e) const
{
    storeAppendPrintf(e,
                      "%s persistent connection counts:\n"
                      "\n"
                      "\t Requests\t Connection Count\n"
                      "\t --------\t ----------------\n",
                      descr);

    for (int i = 0; i < PCONN_HIST_SZ; ++i) {
        if (hist[i] == 0)
            continue;

        storeAppendPrintf(e, "\t%d\t%d\n", i, hist[i]);
    }
}