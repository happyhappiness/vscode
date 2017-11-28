void
GetIoStats(Mgr::IoActionData& stats)
{
    int i;

    stats.http_reads = IOStats.Http.reads;

    for (i = 0; i < IoStats::histSize; ++i) {
        stats.http_read_hist[i] = IOStats.Http.read_hist[i];
    }

    stats.ftp_reads = IOStats.Ftp.reads;

    for (i = 0; i < IoStats::histSize; ++i) {
        stats.ftp_read_hist[i] = IOStats.Ftp.read_hist[i];
    }

    stats.gopher_reads = IOStats.Gopher.reads;

    for (i = 0; i < IoStats::histSize; ++i) {
        stats.gopher_read_hist[i] = IOStats.Gopher.read_hist[i];
    }
}