bool
DiskdIOStrategy::optionQ2Parse(const char *name, const char *value, int isaReconfig)
{
    if (strcmp(name, "Q2") != 0)
        return false;

    int old_magic2 = magic2;

    magic2 = atoi(value);

    if (!isaReconfig)
        return true;

    if (old_magic2 < magic2) {
        /* See comments in Q1 function above */
        debugs(3, DBG_IMPORTANT, "WARNING: cannot increase cache_dir Q2 value while Squid is running.");
        magic2 = old_magic2;
        return true;
    }

    if (old_magic2 != magic2)
        debugs(3, DBG_IMPORTANT, "cache_dir new Q2 value '" << magic2 << "'");

    return true;
}