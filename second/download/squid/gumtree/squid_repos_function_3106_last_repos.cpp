void
storeRebuildProgress(int sd_index, int total, int sofar)
{
    static time_t last_report = 0;
    double n = 0.0;
    double d = 0.0;

    if (sd_index < 0)
        return;

    if (sd_index >= Config.cacheSwap.n_configured)
        return;

    if (NULL == RebuildProgress)
        return;

    RebuildProgress[sd_index].total = total;

    RebuildProgress[sd_index].scanned = sofar;

    if (squid_curtime - last_report < 15)
        return;

    for (sd_index = 0; sd_index < Config.cacheSwap.n_configured; ++sd_index) {
        n += (double) RebuildProgress[sd_index].scanned;
        d += (double) RebuildProgress[sd_index].total;
    }

    debugs(20, DBG_IMPORTANT, "Store rebuilding is "<< std::setw(4)<< std::setprecision(2) << 100.0 * n / d << "% complete");
    last_report = squid_curtime;
}