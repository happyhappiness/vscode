bool
StoreMetaURL::checkConsistency(StoreEntry *e) const
{
    assert (getType() == STORE_META_URL);

    if (!e->mem_obj->url)
        return true;

    if (strcasecmp(e->mem_obj->url, (char *)value)) {
        debugs(20, DBG_IMPORTANT, "storeClientReadHeader: URL mismatch");
        debugs(20, DBG_IMPORTANT, "\t{" << (char *) value << "} != {" << e->mem_obj->url << "}");
        return false;
    }

    return true;
}