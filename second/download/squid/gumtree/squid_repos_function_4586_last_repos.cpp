void
Store::Controller::updateOnNotModified(StoreEntry *old, const StoreEntry &newer)
{
    /* update the old entry object */
    Must(old);
    HttpReply *oldReply = const_cast<HttpReply*>(old->getReply());
    Must(oldReply);

    const bool modified = oldReply->updateOnNotModified(newer.getReply());
    if (!old->timestampsSet() && !modified)
        return;

    /* update stored image of the old entry */

    if (memStore && old->mem_status == IN_MEMORY && !EBIT_TEST(old->flags, ENTRY_SPECIAL))
        memStore->updateHeaders(old);

    if (old->swap_dirn > -1)
        swapDir->updateHeaders(old);
}