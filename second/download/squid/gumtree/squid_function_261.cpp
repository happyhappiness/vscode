static void
stat_io_get(StoreEntry * sentry)
{
    int i;

    storeAppendPrintf(sentry, "HTTP I/O\n");
    storeAppendPrintf(sentry, "number of reads: %d\n", IOStats.Http.reads);
    storeAppendPrintf(sentry, "Read Histogram:\n");

    for (i = 0; i < 16; i++) {
        storeAppendPrintf(sentry, "%5d-%5d: %9d %2d%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          IOStats.Http.read_hist[i],
                          Math::intPercent(IOStats.Http.read_hist[i], IOStats.Http.reads));
    }

    storeAppendPrintf(sentry, "\n");
    storeAppendPrintf(sentry, "FTP I/O\n");
    storeAppendPrintf(sentry, "number of reads: %d\n", IOStats.Ftp.reads);
    storeAppendPrintf(sentry, "Read Histogram:\n");

    for (i = 0; i < 16; i++) {
        storeAppendPrintf(sentry, "%5d-%5d: %9d %2d%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          IOStats.Ftp.read_hist[i],
                          Math::intPercent(IOStats.Ftp.read_hist[i], IOStats.Ftp.reads));
    }

    storeAppendPrintf(sentry, "\n");
    storeAppendPrintf(sentry, "Gopher I/O\n");
    storeAppendPrintf(sentry, "number of reads: %d\n", IOStats.Gopher.reads);
    storeAppendPrintf(sentry, "Read Histogram:\n");

    for (i = 0; i < 16; i++) {
        storeAppendPrintf(sentry, "%5d-%5d: %9d %2d%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          IOStats.Gopher.read_hist[i],
                          Math::intPercent(IOStats.Gopher.read_hist[i], IOStats.Gopher.reads));
    }

    storeAppendPrintf(sentry, "\n");
}