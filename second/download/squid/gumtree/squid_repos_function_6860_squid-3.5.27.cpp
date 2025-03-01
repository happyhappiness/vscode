void
Ipc::ReadWriteLockStats::dump(StoreEntry &e) const
{
    storeAppendPrintf(&e, "Available locks: %9d\n", count);

    if (!count)
        return;

    storeAppendPrintf(&e, "Reading: %9d %6.2f%%\n",
                      readable, (100.0 * readable / count));
    storeAppendPrintf(&e, "Writing: %9d %6.2f%%\n",
                      writeable, (100.0 * writeable / count));
    storeAppendPrintf(&e, "Idle:    %9d %6.2f%%\n",
                      idle, (100.0 * idle / count));

    if (readers || writers) {
        const int locked = readers + writers;
        storeAppendPrintf(&e, "Readers:         %9d %6.2f%%\n",
                          readers, (100.0 * readers / locked));
        const double appPerc = writers ? (100.0 * appenders / writers) : 0.0;
        storeAppendPrintf(&e, "Writers:         %9d %6.2f%% including Appenders: %9d %6.2f%%\n",
                          writers, (100.0 * writers / locked),
                          appenders, appPerc);
    }
}