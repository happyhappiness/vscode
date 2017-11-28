void
store_client::fileRead()
{
    MemObject *mem = entry->mem_obj;

    assert(_callback.pending());
    assert(!flags.disk_io_pending);
    flags.disk_io_pending = 1;

    if (mem->swap_hdr_sz != 0)
        if (entry->swap_status == SWAPOUT_WRITING)
            assert(mem->swapout.sio->offset() > copyInto.offset + (int64_t)mem->swap_hdr_sz);

    storeRead(swapin_sio,
              copyInto.data,
              copyInto.length,
              copyInto.offset + mem->swap_hdr_sz,
              mem->swap_hdr_sz == 0 ? storeClientReadHeader
              : storeClientReadBody,
              this);
}