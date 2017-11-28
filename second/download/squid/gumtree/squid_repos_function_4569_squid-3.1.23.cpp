StoreIOState::Pointer
CossSwapDir::openStoreIO(StoreEntry & e, StoreIOState::STFNCB * file_callback,
                         StoreIOState::STIOCB * callback, void *callback_data)
{
    char *p;
    CossState *cstate;
    sfileno f = e.swap_filen;

    debugs(79, 3, "storeCossOpen: offset " << f);
    StoreFScoss::GetInstance().stats.open.ops++;

    StoreIOState::Pointer sio = new CossState (this);
    cstate = dynamic_cast<CossState *>(sio.getRaw());

    sio->swap_filen = f;
    sio->swap_dirn = index;
    sio->offset_ = 0;
    sio->mode = O_RDONLY | O_BINARY;
    sio->callback = callback;
    sio->file_callback = file_callback;
    sio->callback_data = cbdataReference(callback_data);
    cstate->st_size = e.swap_file_sz;
    sio->e = &e;

    cstate->flags.writing = 0;
    cstate->flags.reading = 0;
    cstate->readbuffer = NULL;
    cstate->reqdiskoffset = -1;
    p = storeCossMemPointerFromDiskOffset(storeCossFilenoToDiskOffset(f), NULL);
    /* make local copy so we don't have to lock membuf */

    if (p) {
        cstate->readbuffer = (char *)xmalloc(cstate->st_size);
        xmemcpy(cstate->readbuffer, p, cstate->st_size);
        StoreFScoss::GetInstance().stats.open_mem_hits++;
    } else {
        /* Do the allocation */
        /* this is the first time we've been called on a new sio
         * read the whole object into memory, then return the
         * requested amount
         */
        StoreFScoss::GetInstance().stats.open_mem_misses++;
        /*
         * This bit of code actually does the LRU disk thing - we realloc
         * a place for the object here, and the file_read() reads the object
         * into the cossmembuf for later writing ..
         */
        cstate->reqdiskoffset = storeCossFilenoToDiskOffset(sio->swap_filen);
        sio->swap_filen = -1;
        sio->swap_filen = allocate(&e, COSS_ALLOC_REALLOC);

        if (sio->swap_filen == -1) {
            /* We have to clean up neatly .. */
            StoreFScoss::GetInstance().stats.open.fail++;
            numcollisions++;
            debugs(79, 2, "storeCossOpen: Reallocation of " << e.swap_dirn << "/" << e.swap_filen << " failed");
            /* XXX XXX XXX Will squid call storeUnlink for this object? */
            return NULL;
        }

        /* Notify the upper levels that we've changed file number */
        sio->file_callback(sio->callback_data, 0, sio);

        /*
         * lock the buffer so it doesn't get swapped out on us
         * this will get unlocked in storeCossClose
         */
        cstate->lockMemBuf();

        /*
         * Do the index magic to keep the disk and memory LRUs identical
         */
        storeCossRemove(this, &e);

        storeCossAdd(this, &e);

        /*
        	 * NOTE cstate->readbuffer is NULL.  We'll actually read
        	 * the disk data into the MemBuf in storeCossRead() and
        	 * return that pointer back to the caller
         	 */
    }

    StoreFScoss::GetInstance().stats.open.success++;
    return sio;
}