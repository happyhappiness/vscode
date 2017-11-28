bool
StoreMeta::checkConsistency(StoreEntry *e) const
{
    switch (getType()) {

    case STORE_META_KEY:

    case STORE_META_URL:

    case STORE_META_VARY_HEADERS:
        assert(0);
        break;

    case STORE_META_STD:
        break;

    case STORE_META_STD_LFS:
        break;

    case STORE_META_OBJSIZE:
        break;

    default:
        debugs(20, DBG_IMPORTANT, "WARNING: got unused STORE_META type " << getType());
        break;
    }

    return true;
}