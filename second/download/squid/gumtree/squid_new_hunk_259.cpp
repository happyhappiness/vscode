
    storeAppendPrintf(e, "Totals since cache startup:\n");

    statCountersDump(e);
}

void
GetIoStats(Mgr::IoActionData& stats)
{
    int i;

    stats.http_reads = IOStats.Http.reads;

    for (i = 0; i < _iostats::histSize; ++i) {
        stats.http_read_hist[i] = IOStats.Http.read_hist[i];
    }

    stats.ftp_reads = IOStats.Ftp.reads;

    for (i = 0; i < _iostats::histSize; ++i) {
        stats.ftp_read_hist[i] = IOStats.Ftp.read_hist[i];
    }

    stats.gopher_reads = IOStats.Gopher.reads;

    for (i = 0; i < _iostats::histSize; ++i) {
        stats.gopher_read_hist[i] = IOStats.Gopher.read_hist[i];
    }
}

void
DumpIoStats(Mgr::IoActionData& stats, StoreEntry* sentry)
{
    int i;

    storeAppendPrintf(sentry, "HTTP I/O\n");
    storeAppendPrintf(sentry, "number of reads: %.0f\n", stats.http_reads);
    storeAppendPrintf(sentry, "Read Histogram:\n");

    for (i = 0; i < _iostats::histSize; ++i) {
        storeAppendPrintf(sentry, "%5d-%5d: %9.0f %2.0f%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          stats.http_read_hist[i],
                          Math::doublePercent(stats.http_read_hist[i], stats.http_reads));
    }

    storeAppendPrintf(sentry, "\n");
    storeAppendPrintf(sentry, "FTP I/O\n");
    storeAppendPrintf(sentry, "number of reads: %.0f\n", stats.ftp_reads);
    storeAppendPrintf(sentry, "Read Histogram:\n");

    for (i = 0; i < _iostats::histSize; ++i) {
        storeAppendPrintf(sentry, "%5d-%5d: %9.0f %2.0f%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          stats.ftp_read_hist[i],
                          Math::doublePercent(stats.ftp_read_hist[i], stats.ftp_reads));
    }

    storeAppendPrintf(sentry, "\n");
    storeAppendPrintf(sentry, "Gopher I/O\n");
    storeAppendPrintf(sentry, "number of reads: %.0f\n", stats.gopher_reads);
    storeAppendPrintf(sentry, "Read Histogram:\n");

    for (i = 0; i < _iostats::histSize; ++i) {
        storeAppendPrintf(sentry, "%5d-%5d: %9.0f %2.0f%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          stats.gopher_read_hist[i],
                          Math::doublePercent(stats.gopher_read_hist[i], stats.gopher_reads));
    }

    storeAppendPrintf(sentry, "\n");
}

static const char *
