HttpReply const *
StoreEntry::getReply () const
{
    if (NULL == mem_obj)
        return NULL;

    return mem_obj->getReply();
}