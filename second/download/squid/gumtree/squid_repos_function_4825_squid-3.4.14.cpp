sfileno
CossSwapDir::allocate(const StoreEntry * e, int which)
{
    CossMemBuf *newmb;
    off_t retofs;
    off_t allocsize;
    int coll = 0;
    sfileno checkf;

    /* Make sure we chcek collisions if reallocating */

    if (which == COSS_ALLOC_REALLOC) {
        checkf = e->swap_filen;
        ++ StoreFScoss::GetInstance().stats.alloc.realloc;
    } else {
        checkf = -1;
        ++ StoreFScoss::GetInstance().stats.alloc.alloc;
    }

    if (e->swap_file_sz > 0)
        allocsize = e->swap_file_sz;
    else
        allocsize = e->objectLen() + e->mem_obj->swap_hdr_sz;

    /* Check if we have overflowed the disk .. */
    if (current_offset + allocsize > static_cast<int64_t>(maxSize())) {
        /*
         * tried to allocate past the end of the disk, so wrap
         * back to the beginning
         */
        ++ StoreFScoss::GetInstance().stats.disk_overflows;
        current_membuf->flags.full = true;
        current_membuf->diskend = current_offset;
        current_membuf->maybeWrite(this);
        current_offset = 0;	/* wrap back to beginning */
        debugs(79, 2, "CossSwapDir::allocate: wrap to 0");

        newmb = createMemBuf(0, checkf, &coll);
        current_membuf = newmb;

        /* Check if we have overflowed the MemBuf */
    } else if ((current_offset + allocsize) >= current_membuf->diskend) {
        /*
         * Skip the blank space at the end of the stripe. start over.
         */
        ++ StoreFScoss::GetInstance().stats.stripe_overflows;
        current_membuf->flags.full = true;
        current_offset = current_membuf->diskend;
        current_membuf->maybeWrite(this);
        debugs(79, 2, "CossSwapDir::allocate: New offset - " << current_offset);
        newmb = createMemBuf(current_offset, checkf, &coll);
        current_membuf = newmb;
    }

    /*
     * If we didn't get a collision, then update the current offset
     * and return it
     */
    if (coll == 0) {
        retofs = current_offset;
        current_offset = retofs + allocsize;
        /* round up to our blocksize */
        current_offset = ((current_offset + blksz_mask) >> blksz_bits ) << blksz_bits;
        return storeCossDiskOffsetToFileno(retofs);
    } else {
        ++ StoreFScoss::GetInstance().stats.alloc.collisions;
        debugs(79, 3, "CossSwapDir::allocate: Collision");
        return -1;
    }
}