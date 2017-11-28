void
Fs::Ufs::RebuildState::rebuildStep()
{
    currentEntry(NULL);

    // Balance our desire to maximize the number of entries processed at once
    // (and, hence, minimize overheads and total rebuild time) with a
    // requirement to also process Coordinator events, disk I/Os, etc.
    const int maxSpentMsec = 50; // keep small: most RAM I/Os are under 1ms
    const timeval loopStart = current_time;

    const int totalEntries = LogParser ? LogParser->SwapLogEntries() : -1;

    while (!isDone()) {
        if (fromLog)
            rebuildFromSwapLog();
        else
            rebuildFromDirectory();

        // TODO: teach storeRebuildProgress to handle totalEntries <= 0
        if (totalEntries > 0 && (n_read % 4000 == 0))
            storeRebuildProgress(sd->index, totalEntries, n_read);

        if (opt_foreground_rebuild)
            continue; // skip "few entries at a time" check below

        getCurrentTime();
        const double elapsedMsec = tvSubMsec(loopStart, current_time);
        if (elapsedMsec > maxSpentMsec || elapsedMsec < 0) {
            debugs(47, 5, HERE << "pausing after " << n_read << " entries in " <<
                   elapsedMsec << "ms; " << (elapsedMsec/n_read) << "ms per entry");
            break;
        }
    }
}