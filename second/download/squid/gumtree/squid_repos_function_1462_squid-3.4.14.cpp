bool
StoreEntry::mayStartSwapOut()
{
    // must be checked in the caller
    assert(!EBIT_TEST(flags, ENTRY_ABORTED));
    assert(!swappingOut());

    if (!Config.cacheSwap.n_configured)
        return false;

    assert(mem_obj);
    MemObject::SwapOut::Decision &decision = mem_obj->swapout.decision;

    // if we decided that swapout is not possible, do not repeat same checks
    if (decision == MemObject::SwapOut::swImpossible) {
        debugs(20, 3, HERE << " already rejected");
        return false;
    }

    // if we decided that swapout is possible, do not repeat same checks
    if (decision == MemObject::SwapOut::swPossible) {
        debugs(20, 3,  HERE << "already allowed");
        return true;
    }

    // if we swapped out already, do not start over
    if (swap_status == SWAPOUT_DONE) {
        debugs(20, 3,  HERE << "already did");
        decision = MemObject::SwapOut::swImpossible;
        return false;
    }

    if (!checkCachable()) {
        debugs(20, 3,  HERE << "not cachable");
        decision = MemObject::SwapOut::swImpossible;
        return false;
    }

    if (EBIT_TEST(flags, ENTRY_SPECIAL)) {
        debugs(20, 3,  HERE  << url() << " SPECIAL");
        decision = MemObject::SwapOut::swImpossible;
        return false;
    }

    if (mem_obj->inmem_lo > 0) {
        debugs(20, 3, "storeSwapOut: (inmem_lo > 0)  imem_lo:" <<  mem_obj->inmem_lo);
        decision = MemObject::SwapOut::swImpossible;
        return false;
    }

    if (!mem_obj->isContiguous()) {
        debugs(20, 3, "storeSwapOut: not Contiguous");
        decision = MemObject::SwapOut::swImpossible;
        return false;
    }

    // check cache_dir max-size limit if all cache_dirs have it
    if (store_maxobjsize >= 0) {
        // TODO: add estimated store metadata size to be conservative

        // use guaranteed maximum if it is known
        const int64_t expectedEnd = mem_obj->expectedReplySize();
        debugs(20, 7,  HERE << "expectedEnd = " << expectedEnd);
        if (expectedEnd > store_maxobjsize) {
            debugs(20, 3,  HERE << "will not fit: " << expectedEnd <<
                   " > " << store_maxobjsize);
            decision = MemObject::SwapOut::swImpossible;
            return false; // known to outgrow the limit eventually
        }

        // use current minimum (always known)
        const int64_t currentEnd = mem_obj->endOffset();
        if (currentEnd > store_maxobjsize) {
            debugs(20, 3,  HERE << "does not fit: " << currentEnd <<
                   " > " << store_maxobjsize);
            decision = MemObject::SwapOut::swImpossible;
            return false; // already does not fit and may only get bigger
        }

        // prevent final default swPossible answer for yet unknown length
        if (expectedEnd < 0 && store_status != STORE_OK) {
            const int64_t maxKnownSize = mem_obj->availableForSwapOut();
            debugs(20, 7, HERE << "maxKnownSize= " << maxKnownSize);
            /*
             * NOTE: the store_maxobjsize here is the global maximum
             * size of object cacheable in any of Squid cache stores
             * both disk and memory stores.
             *
             * However, I am worried that this
             * deferance may consume a lot of memory in some cases.
             * Should we add an option to limit this memory consumption?
             */
            debugs(20, 5,  HERE << "Deferring swapout start for " <<
                   (store_maxobjsize - maxKnownSize) << " bytes");
            return true; // may still fit, but no final decision yet
        }
    }

    decision = MemObject::SwapOut::swPossible;
    return true;
}