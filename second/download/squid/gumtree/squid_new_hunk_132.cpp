    storeAppendPrintf(sentry, "\t\tRestore: %d\n", restore_bps);
}

void
DelaySpec::dump (StoreEntry *entry) const
{
    storeAppendPrintf(entry, " %d/%" PRId64 "", restore_bps, max_bytes);
}

void
DelaySpec::parse()
{
    int r;
