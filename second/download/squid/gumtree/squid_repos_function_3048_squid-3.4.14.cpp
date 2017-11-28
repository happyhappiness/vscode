int
StoreEntry::checkTooSmall()
{
    if (EBIT_TEST(flags, ENTRY_SPECIAL))
        return 0;

    if (STORE_OK == store_status)
        if (mem_obj->object_sz < 0 ||
                mem_obj->object_sz < Config.Store.minObjectSize)
            return 1;
    if (getReply()->content_length > -1)
        if (getReply()->content_length < Config.Store.minObjectSize)
            return 1;
    return 0;
}