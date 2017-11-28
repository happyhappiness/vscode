bool
StoreEntry::checkCachable()
{
    // XXX: This method is used for both memory and disk caches, but some
    // checks are specific to disk caches. Move them to mayStartSwapOut().

    // XXX: This method may be called several times, sometimes with different
    // outcomes, making store_check_cachable_hist counters misleading.

    // check this first to optimize handling of repeated calls for uncachables
    if (EBIT_TEST(flags, RELEASE_REQUEST)) {
        debugs(20, 2, "StoreEntry::checkCachable: NO: not cachable");
        ++store_check_cachable_hist.no.not_entry_cachable; // TODO: rename?
        return 0; // avoid rerequesting release below
    }

#if CACHE_ALL_METHODS

    if (mem_obj->method != Http::METHOD_GET) {
        debugs(20, 2, "StoreEntry::checkCachable: NO: non-GET method");
        ++store_check_cachable_hist.no.non_get;
    } else
#endif
        if (store_status == STORE_OK && EBIT_TEST(flags, ENTRY_BAD_LENGTH)) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: wrong content-length");
            ++store_check_cachable_hist.no.wrong_content_length;
        } else if (EBIT_TEST(flags, ENTRY_NEGCACHED)) {
            debugs(20, 3, "StoreEntry::checkCachable: NO: negative cached");
            ++store_check_cachable_hist.no.negative_cached;
            return 0;           /* avoid release call below */
        } else if (!mem_obj || !getReply()) {
            // XXX: In bug 4131, we forgetHit() without mem_obj, so we need
            // this segfault protection, but how can we get such a HIT?
            debugs(20, 2, "StoreEntry::checkCachable: NO: missing parts: " << *this);
            ++store_check_cachable_hist.no.missing_parts;
        } else if (checkTooBig()) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too big");
            ++store_check_cachable_hist.no.too_big;
        } else if (checkTooSmall()) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too small");
            ++store_check_cachable_hist.no.too_small;
        } else if (EBIT_TEST(flags, KEY_PRIVATE)) {
            debugs(20, 3, "StoreEntry::checkCachable: NO: private key");
            ++store_check_cachable_hist.no.private_key;
        } else if (swap_status != SWAPOUT_NONE) {
            /*
             * here we checked the swap_status because the remaining
             * cases are only relevant only if we haven't started swapping
             * out the object yet.
             */
            return 1;
        } else if (storeTooManyDiskFilesOpen()) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too many disk files open");
            ++store_check_cachable_hist.no.too_many_open_files;
        } else if (fdNFree() < RESERVED_FD) {
            debugs(20, 2, "StoreEntry::checkCachable: NO: too many FD's open");
            ++store_check_cachable_hist.no.too_many_open_fds;
        } else {
            ++store_check_cachable_hist.yes.Default;
            return 1;
        }

    releaseRequest();
    return 0;
}