    mbdata = MemBlob::GetStats();
    sbsizesatdestruct = collectSBufDestructTimeStats();
    mbsizesatdestruct = collectMemBlobDestructTimeStats();
}

static void
statHistSBufDumper(StoreEntry * sentry, int idx, double val, double size, int count)
{
    if (count == 0)
        return;
    storeAppendPrintf(sentry, "\t%d-%d\t%d\n", static_cast<int>(val), static_cast<int>(val+size), count);
}

void
SBufStatsAction::dump(StoreEntry* entry)
{
    StoreEntryStream ses(entry);
    ses << "\n\n\nThese statistics are experimental; their format and contents "
        "should not be relied upon, they are bound to change as "
        "the SBuf feature is evolved\n";
    sbdata.dump(ses);
    mbdata.dump(ses);
    ses << "\n";
