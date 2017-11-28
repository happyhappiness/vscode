tlv *
storeSwapMetaBuild(StoreEntry * e)
{
    tlv *TLV = NULL;		/* we'll return this */
    tlv **T = &TLV;
    const char *url;
    const char *vary;
    assert(e->mem_obj != NULL);
    const int64_t objsize = e->mem_obj->expectedReplySize();
    assert(e->swap_status == SWAPOUT_WRITING);
    url = e->url();
    debugs(20, 3, "storeSwapMetaBuild: " << url  );
    tlv *t = StoreMeta::Factory (STORE_META_KEY,SQUID_MD5_DIGEST_LENGTH, e->key);

    if (!t) {
        storeSwapTLVFree(TLV);
        return NULL;
    }

    T = StoreMeta::Add(T, t);
    t = StoreMeta::Factory(STORE_META_STD_LFS,STORE_HDR_METASIZE,&e->timestamp);

    if (!t) {
        storeSwapTLVFree(TLV);
        return NULL;
    }

    T = StoreMeta::Add(T, t);
    t = StoreMeta::Factory(STORE_META_URL, strlen(url) + 1, url);

    if (!t) {
        storeSwapTLVFree(TLV);
        return NULL;
    }

    if (objsize >= 0) {
        T = StoreMeta::Add(T, t);
        t = StoreMeta::Factory(STORE_META_OBJSIZE, sizeof(objsize), &objsize);

        if (!t) {
            storeSwapTLVFree(TLV);
            return NULL;
        }
    }

    T = StoreMeta::Add(T, t);
    vary = e->mem_obj->vary_headers;

    if (vary) {
        t =StoreMeta::Factory(STORE_META_VARY_HEADERS, strlen(vary) + 1, vary);

        if (!t) {
            storeSwapTLVFree(TLV);
            return NULL;
        }

        StoreMeta::Add (T, t);
    }

    return TLV;
}