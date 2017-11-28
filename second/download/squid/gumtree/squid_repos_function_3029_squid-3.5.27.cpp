store_client_t
StoreEntry::storeClientType() const
{
    /* The needed offset isn't in memory
     * XXX TODO: this is wrong for range requests
     * as the needed offset may *not* be 0, AND
     * offset 0 in the memory object is the HTTP headers.
     */

    assert(mem_obj);

    if (mem_obj->inmem_lo)
        return STORE_DISK_CLIENT;

    if (EBIT_TEST(flags, ENTRY_ABORTED)) {
        /* I don't think we should be adding clients to aborted entries */
        debugs(20, DBG_IMPORTANT, "storeClientType: adding to ENTRY_ABORTED entry");
        return STORE_MEM_CLIENT;
    }

    if (store_status == STORE_OK) {
        /* the object has completed. */

        if (mem_obj->inmem_lo == 0 && !isEmpty()) {
            if (swap_status == SWAPOUT_DONE) {
                debugs(20,7, HERE << mem_obj << " lo: " << mem_obj->inmem_lo << " hi: " << mem_obj->endOffset() << " size: " << mem_obj->object_sz);
                if (mem_obj->endOffset() == mem_obj->object_sz) {
                    /* hot object fully swapped in (XXX: or swapped out?) */
                    return STORE_MEM_CLIENT;
                }
            } else {
                /* Memory-only, or currently being swapped out */
                return STORE_MEM_CLIENT;
            }
        }
        return STORE_DISK_CLIENT;
    }

    /* here and past, entry is STORE_PENDING */
    /*
     * If this is the first client, let it be the mem client
     */
    if (mem_obj->nclients == 1)
        return STORE_MEM_CLIENT;

    /*
     * If there is no disk file to open yet, we must make this a
     * mem client.  If we can't open the swapin file before writing
     * to the client, there is no guarantee that we will be able
     * to open it later when we really need it.
     */
    if (swap_status == SWAPOUT_NONE)
        return STORE_MEM_CLIENT;

    /*
     * otherwise, make subsequent clients read from disk so they
     * can not delay the first, and vice-versa.
     */
    return STORE_DISK_CLIENT;
}