int64_t
MemObject::objectBytesOnDisk() const
{
    /*
     * NOTE: storeOffset() represents the disk file size,
     * not the amount of object data on disk.
     *
     * If we don't have at least 'swap_hdr_sz' bytes
     * then none of the object data is on disk.
     *
     * This should still be safe if swap_hdr_sz == 0,
     * meaning we haven't even opened the swapout file
     * yet.
     */

    if (swapout.sio.getRaw() == NULL)
        return 0;

    int64_t nwritten = swapout.sio->offset();

    if (nwritten <= (int64_t)swap_hdr_sz)
        return 0;

    return (nwritten - swap_hdr_sz);
}