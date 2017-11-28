Mgr::IoActionData&
Mgr::IoActionData::operator += (const IoActionData& stats)
{
    http_reads += stats.http_reads;
    for (int i = 0; i < IoStats::histSize; ++i)
        http_read_hist[i] += stats.http_read_hist[i];
    ftp_reads += stats.ftp_reads;
    for (int i = 0; i < IoStats::histSize; ++i)
        ftp_read_hist[i] += stats.ftp_read_hist[i];
    gopher_reads += stats.gopher_reads;
    for (int i = 0; i < IoStats::histSize; ++i)
        gopher_read_hist[i] += stats.gopher_read_hist[i];

    return *this;
}