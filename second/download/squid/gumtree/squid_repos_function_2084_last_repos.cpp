bool
StoreMetaVary::checkConsistency(StoreEntry *e) const
{
    assert (getType() == STORE_META_VARY_HEADERS);

    if (e->mem_obj->vary_headers.isEmpty()) {
        /* XXX separate this mutator from the query */
        /* Assume the object is OK.. remember the vary request headers */
        e->mem_obj->vary_headers.assign(static_cast<const char *>(value), length);
        /* entries created before SBuf vary handling may include string terminator */
        static const SBuf nul("\0", 1);
        e->mem_obj->vary_headers.trim(nul);
        return true;
    }

    if (e->mem_obj->vary_headers.cmp(static_cast<const char *>(value), length) != 0)
        return false;

    return true;
}