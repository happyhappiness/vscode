void
StoreEntry::purgeMem()
{
    if (mem_obj == NULL)
        return;

    debugs(20, 3, "StoreEntry::purgeMem: Freeing memory-copy of " << getMD5Text());

    destroyMemObject();

    if (swap_status != SWAPOUT_DONE)
        release();
}