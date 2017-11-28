int64_t
Transients::EntryLimit()
{
    // TODO: we should also check whether any SMP-aware caching is configured
    if (!UsingSmp() || !Config.onoff.collapsed_forwarding)
        return 0; // no SMP collapsed forwarding possible or needed

    return Config.collapsed_forwarding_shared_entries_limit;
}