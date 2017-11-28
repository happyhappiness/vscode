int
StoreEntry::keepInMemory() const
{
    if (mem_obj == NULL)
        return 0;

    if (mem_obj->data_hdr.size() == 0)
        return 0;

    return mem_obj->inmem_lo == 0;
}