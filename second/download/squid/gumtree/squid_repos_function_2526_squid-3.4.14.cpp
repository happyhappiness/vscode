bool
StoreMetaVary::checkConsistency(StoreEntry *e) const
{
    assert (getType() == STORE_META_VARY_HEADERS);

    if (!e->mem_obj->vary_headers) {
        /* XXX separate this mutator from the query */
        /* Assume the object is OK.. remember the vary request headers */
        e->mem_obj->vary_headers = xstrdup((char *)value);
        return true;
    }

    if (strcmp(e->mem_obj->vary_headers, (char *)value) != 0)
        return false;

    return true;
}