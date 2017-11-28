void
MemObject::reset()
{
    assert(swapout.sio == NULL);
    data_hdr.freeContent();
    inmem_lo = 0;
    /* Should we check for clients? */
}