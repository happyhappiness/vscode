void
PconnPool::dumpHist(StoreEntry * e)
{
    int i;
    storeAppendPrintf(e,
                      "%s persistent connection counts:\n"
                      "\n"
                      "\treq/\n"
                      "\tconn      count\n"
                      "\t----  ---------\n",
                      descr);

    for (i = 0; i < PCONN_HIST_SZ; i++) {
        if (hist[i] == 0)
            continue;

        storeAppendPrintf(e, "\t%4d  %9d\n", i, hist[i]);
    }
}