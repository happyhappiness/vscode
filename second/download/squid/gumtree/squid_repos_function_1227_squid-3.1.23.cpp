bool
StoreMeta::validType(char type)
{
    /* VOID is reserved, and new types have to be added as classes */
    if (type <= STORE_META_VOID || type >= STORE_META_END + 10) {
        debugs(20, 0, "storeSwapMetaUnpack: bad type (" << type << ")!");
        return false;
    }

    /* Not yet implemented */
    if (type >= STORE_META_END ||
            type == STORE_META_STOREURL ||
            type == STORE_META_VARY_ID) {
        debugs(20, 3, "storeSwapMetaUnpack: Not yet implemented (" << type << ") in disk metadata");
        return false;
    }

    /* Unused in any current squid code */
    if (type == STORE_META_KEY_URL ||
            type == STORE_META_KEY_SHA ||
            type == STORE_META_HITMETERING ||
            type == STORE_META_VALID) {
        debugs(20, 0, "Obsolete and unused type (" << type << ") in disk metadata");
        return false;
    }

    return true;
}