void
StoreEntry::setNoDelay(bool const newValue)
{
    if (mem_obj)
        mem_obj->setNoDelay(newValue);
}