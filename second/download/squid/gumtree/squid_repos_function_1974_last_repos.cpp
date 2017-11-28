bool
store_client::moreToSend() const
{
    if (entry->store_status == STORE_PENDING)
        return true; // there may be more coming

    /* STORE_OK, including aborted entries: no more data is coming */

    const int64_t len = entry->objectLen();

    // If we do not know the entry length, then we have to open the swap file.
    const bool canSwapIn = entry->swap_filen >= 0;
    if (len < 0)
        return canSwapIn;

    if (copyInto.offset >= len)
        return false; // sent everything there is

    if (canSwapIn)
        return true; // if we lack prefix, we can swap it in

    // If we cannot swap in, make sure we have what we want in RAM. Otherwise,
    // scheduleRead calls scheduleDiskRead which asserts without a swap file.
    const MemObject *mem = entry->mem_obj;
    return mem &&
           mem->inmem_lo <= copyInto.offset && copyInto.offset < mem->endOffset();
}