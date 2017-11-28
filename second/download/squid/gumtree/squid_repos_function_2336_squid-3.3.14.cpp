void
store_client::scheduleRead()
{
    MemObject *mem = entry->mem_obj;

    if (copyInto.offset >= mem->inmem_lo && copyInto.offset < mem->endOffset())
        scheduleMemRead();
    else
        scheduleDiskRead();
}