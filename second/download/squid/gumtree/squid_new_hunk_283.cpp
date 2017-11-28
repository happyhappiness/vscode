{
    if (flags.read_only)
        storeAppendPrintf(e, " no-store");
}

bool
SwapDir::optionObjectSizeParse(char const *option, const char *value, int isaReconfig)
{
    int64_t *val;
    if (strcmp(option, "max-size") == 0) {
        val = &max_objsize;
    } else if (strcmp(option, "min-size") == 0) {
        val = &min_objsize;
    } else
        return false;

    if (!value)
        self_destruct();

    int64_t size = strtoll(value, NULL, 10);

    if (isaReconfig && *val != size) {
        if (allowOptionReconfigure(option)) {
            debugs(3, DBG_IMPORTANT, "cache_dir '" << path << "' object " <<
                   option << " now " << size << " Bytes");
        } else {
            debugs(3, DBG_IMPORTANT, "WARNING: cache_dir '" << path << "' "
                   "object " << option << " cannot be changed dynamically, " <<
                   "value left unchanged (" << *val << " Bytes)");
            return true;
        }
    }

    *val = size;

    return true;
}

void
SwapDir::optionObjectSizeDump(StoreEntry * e) const
{
    if (min_objsize != 0)
        storeAppendPrintf(e, " min-size=%" PRId64, min_objsize);

    if (max_objsize != -1)
        storeAppendPrintf(e, " max-size=%" PRId64, max_objsize);
}

// some SwapDirs may maintain their indexes and be able to lookup an entry key
StoreEntry *
SwapDir::get(const cache_key *key)
{
    return NULL;
}

void
SwapDir::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}
