bool
StoreEntry::checkTooBig() const
{
    if (mem_obj->endOffset() > store_maxobjsize)
        return true;

    if (getReply()->content_length < 0)
        return false;

    return (getReply()->content_length > store_maxobjsize);
}