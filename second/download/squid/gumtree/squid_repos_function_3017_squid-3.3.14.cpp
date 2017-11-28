void
StoreEntry::negativeCache()
{
    // XXX: should make the default for expires 0 instead of -1
    //      so we can distinguish "Expires: -1" from nothing.
    if (expires <= 0)
#if USE_HTTP_VIOLATIONS
        expires = squid_curtime + Config.negativeTtl;
#else
        expires = squid_curtime;
#endif
    EBIT_SET(flags, ENTRY_NEGCACHED);
}