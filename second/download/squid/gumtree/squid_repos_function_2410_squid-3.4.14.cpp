void
store_client::scheduleMemRead()
{
    /* What the client wants is in memory */
    /* Old style */
    debugs(90, 3, "store_client::doCopy: Copying normal from memory");
    size_t sz = entry->mem_obj->data_hdr.copy(copyInto);
    callback(sz);
    flags.store_copying = false;
}