bool
StoreEntry::swapOutAble() const
{
    dlink_node *node;

    if (mem_obj->swapout.sio != NULL)
        return true;

    if (mem_obj->inmem_lo > 0)
        return false;

    /*
     * If there are DISK clients, we must write to disk
     * even if its not cachable
     * RBC: Surely we should not create disk client on non cacheable objects?
     * therefore this should be an assert?
     * RBC 20030708: We can use disk to avoid mem races, so this shouldn't be
     * an assert.
     */
    for (node = mem_obj->clients.head; node; node = node->next) {
        if (((store_client *) node->data)->getType() == STORE_DISK_CLIENT)
            return true;
    }

    /* Don't pollute the disk with icons and other special entries */
    if (EBIT_TEST(flags, ENTRY_SPECIAL))
        return false;

    if (!EBIT_TEST(flags, ENTRY_CACHABLE))
        return false;

    if (!mem_obj->isContiguous())
        return false;

    return true;
}