const char *
StoreEntry::url() const
{
    if (mem_obj == NULL)
        return "[null_mem_obj]";
    else
        return mem_obj->storeId();
}