StoreIOState::Pointer
CossSwapDir::createStoreIO(StoreEntry &e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * callback, void *callback_data)
{
    CossState *cstate;
    StoreIOState::Pointer sio = new CossState(this);
    cstate = dynamic_cast<CossState *>(sio.getRaw());
    sio->offset_ = 0;
    sio->mode = O_WRONLY | O_BINARY;

    /*
     * If we get handed an object with a size of -1,
     * the squid code is broken
     */
    assert(e.mem_obj->object_sz != -1);
    StoreFScoss::GetInstance().stats.create.ops++;

    /*
     * this one is kinda strange - Eric called allocate(), then
     * storeCossOpen(O_RDONLY) .. weird. Anyway, I'm allocating this now.
     */
    cstate->st_size = e.objectLen() + e.mem_obj->swap_hdr_sz;
    sio->swap_dirn = index;
    sio->swap_filen = allocate(&e, COSS_ALLOC_ALLOCATE);
    debugs(79, 3, "storeCossCreate: offset " <<
           storeCossFilenoToDiskOffset(sio->swap_filen) <<
           ", size " << (long int) cstate->st_size << ", end " <<
           (sio->swap_filen + cstate->st_size));

    /* assume allocate() always succeeds */
    assert(-1 != sio->swap_filen);

    sio->callback = callback;
    sio->file_callback = file_callback;
    sio->callback_data = cbdataReference(callback_data);
    sio->e = &e;

    cstate->flags.writing = 0;
    cstate->flags.reading = 0;
    cstate->readbuffer = NULL;
    cstate->reqdiskoffset = -1;

    /* Now add it into the index list */
    storeCossAdd(this, &e);

    cstate->lockMemBuf();
    StoreFScoss::GetInstance().stats.create.success++;
    return sio;
}