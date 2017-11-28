StoreMeta *
StoreMeta::Factory (char type, size_t len, void const *value)
{
    if (!validType(type))
        return NULL;

    StoreMeta *result;

    switch (type) {

    case STORE_META_KEY:
        result = new StoreMetaMD5;
        break;

    case STORE_META_URL:
        result = new StoreMetaURL;
        break;

    case STORE_META_STD:
        result = new StoreMetaSTD;
        break;

    case STORE_META_STD_LFS:
        result = new StoreMetaSTDLFS;
        break;

    case STORE_META_OBJSIZE:
        result = new StoreMetaObjSize;
        break;

    case STORE_META_VARY_HEADERS:
        result = new StoreMetaVary;
        break;

    default:
        debugs(20, 0, "Attempt to create unknown concrete StoreMeta");
        return NULL;
    }

    if (!result->validLength(len)) {
        delete result;
        return NULL;
    }

    result->length = len;
    result->value = xmalloc(len);
    xmemcpy(result->value, value, len);
    return result;
}