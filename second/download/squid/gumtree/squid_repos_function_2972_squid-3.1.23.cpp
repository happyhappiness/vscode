int
StoreEntry::checkCachable()
{
#if CACHE_ALL_METHODS

    if (mem_obj->method != METHOD_GET) {
        debugs(20, 2, "StoreEntry::checkCachable: NO: non-GET method");
        store_check_cachable_hist.no.non_get++;
    } else
#endif
        if (store_status == STORE_OK && EBIT_TEST(flags, ENTRY_BAD_LENGTH)) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: wrong content-length");
            store_check_cachable_hist.no.wrong_content_length++;
        } else if (!EBIT_TEST(flags, ENTRY_CACHABLE)) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: not cachable");
            store_check_cachable_hist.no.not_entry_cachable++;
        } else if (EBIT_TEST(flags, ENTRY_NEGCACHED)) {
            debugs(20, 3, "StoreEntry::checkCachable: NO: negative cached");
            store_check_cachable_hist.no.negative_cached++;
            return 0;           /* avoid release call below */
        } else if ((getReply()->content_length > 0 &&
                    getReply()->content_length
                    > Config.Store.maxObjectSize) ||
                   mem_obj->endOffset() > Config.Store.maxObjectSize) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too big");
            store_check_cachable_hist.no.too_big++;
        } else if (getReply()->content_length > Config.Store.maxObjectSize) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too big");
            store_check_cachable_hist.no.too_big++;
        } else if (checkTooSmall()) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too small");
            store_check_cachable_hist.no.too_small++;
        } else if (EBIT_TEST(flags, KEY_PRIVATE)) {
            debugs(20, 3, "StoreEntry::checkCachable: NO: private key");
            store_check_cachable_hist.no.private_key++;
        } else if (swap_status != SWAPOUT_NONE) {
            /*
             * here we checked the swap_status because the remaining
             * cases are only relevant only if we haven't started swapping
             * out the object yet.
             */
            return 1;
        } else if (storeTooManyDiskFilesOpen()) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too many disk files open");
            store_check_cachable_hist.no.too_many_open_files++;
        } else if (fdNFree() < RESERVED_FD) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too many FD's open");
            store_check_cachable_hist.no.too_many_open_fds++;
        } else {
            store_check_cachable_hist.yes.Default++;
            return 1;
        }

    releaseRequest();
    /* StoreEntry::releaseRequest() cleared ENTRY_CACHABLE */
    return 0;
}