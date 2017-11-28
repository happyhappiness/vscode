void
DelaySpec::stats (StoreEntry * sentry, char const *label) const
{
    if (restore_bps == -1) {
        storeAppendPrintf(sentry, "\t%s:\n\t\tDisabled.\n\n", label);
        return;
    }

    storeAppendPrintf(sentry, "\t%s:\n", label);
    storeAppendPrintf(sentry, "\t\tMax: %" PRId64 "\n", max_bytes);
    storeAppendPrintf(sentry, "\t\tRestore: %d\n", restore_bps);
}