bool
StoreMetaURL::checkConsistency(StoreEntry *e) const
{
    assert (getType() == STORE_META_URL);

    if (!e->mem_obj->hasUris())
        return true;

    if (strcasecmp(e->mem_obj->urlXXX(), (char *)value)) {
        debugs(20, DBG_IMPORTANT, "storeClientReadHeader: URL mismatch");
        debugs(20, DBG_IMPORTANT, "\t{" << (char *) value << "} != {" << e->mem_obj->urlXXX() << "}");
        return false;
    }

    return true;
}