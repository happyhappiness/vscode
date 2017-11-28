{
    if (flags.read_only)
        storeAppendPrintf(e, " no-store");
}

bool
SwapDir::optionMaxSizeParse(char const *option, const char *value, int isaReconfig)
{
    if (strcmp(option, "max-size") != 0)
        return false;

    if (!value)
        self_destruct();

    int64_t size = strtoll(value, NULL, 10);

    if (isaReconfig && max_objsize != size)
        debugs(3, 1, "Cache dir '" << path << "' max object size now " << size);

    max_objsize = size;

    return true;
}

void
SwapDir::optionMaxSizeDump(StoreEntry * e) const
{
    if (max_objsize != -1)
        storeAppendPrintf(e, " max-size=%" PRId64, max_objsize);
}

/* Swapdirs do not have an index of their own - thus they ask their parent..
 * but the parent child relationship isn't implemented yet
 */
StoreEntry *

SwapDir::get
(const cache_key *key)
{
    return Store::Root().get(key);
}

void

SwapDir::get
(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}
