void
CossState::write(char const *buf, size_t size, off_t offset, FREE * free_func)
{
    char *dest;
    CossMemBuf *membuf;
    off_t diskoffset;

    /*
     * If we get handed an object with a size of -1,
     * the squid code is broken
     */
    assert(e->mem_obj->object_sz != -1);
    ++ StoreFScoss::GetInstance().stats.write.ops;

    debugs(79, 3, "storeCossWrite: offset " << offset_ << ", len " << (unsigned long int) size);
    diskoffset = SD->storeCossFilenoToDiskOffset(swap_filen) + offset_;
    CossSwapDir *SD = (CossSwapDir *)INDEXSD(swap_dirn);
    dest = SD->storeCossMemPointerFromDiskOffset(diskoffset, &membuf);
    assert(dest != NULL);
    memcpy(dest, buf, size);
    offset_ += size;

    if (free_func)
        (free_func) ((char *)buf);

    ++ StoreFScoss::GetInstance().stats.write.success;
}