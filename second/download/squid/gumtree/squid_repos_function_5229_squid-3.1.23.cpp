void
AIODiskFile::write(WriteRequest *request)
{
    int slot;
    async_queue_entry_t *qe;

    assert(strategy->aq.aq_state == AQ_STATE_SETUP);

    /* Find a free slot */
    slot = strategy->findSlot();

    if (slot < 0) {
        /* No free slot? Callback error, and return */
        fatal("Aiee! out of aiocb slots FIXME and wrap file_write !\n");
        debugs(79, 1, "WARNING: out of aiocb slots!");
        /* fall back to blocking method */
        //        file_write(fd, offset, buf, len, callback, data, freefunc);
        return;
    }

    /* Mark slot as ours */
    qe = &strategy->aq.aq_queue[slot];

    qe->aq_e_state = AQ_ENTRY_USED;

    qe->aq_e_callback_data = cbdataReference(request);

    qe->theFile = cbdataReference(this);

    qe->aq_e_type = AQ_ENTRY_WRITE;

    qe->aq_e_free = request->free_func;

    qe->aq_e_buf = (void *)request->buf;

    qe->aq_e_fd = fd;

    qe->aq_e_aiocb.aio_fildes = fd;

    qe->aq_e_aiocb.aio_nbytes = request->len;

    qe->aq_e_aiocb.aio_offset = request->offset;

    qe->aq_e_aiocb.aio_buf = (void *)request->buf;

    /* Account */
    ++strategy->aq.aq_numpending;

    /* Initiate aio */
    if (aio_write(&qe->aq_e_aiocb) < 0) {
        fatalf("Aiee! aio_write() returned error (%d) FIXME and wrap file_write !\n", errno);
        debugs(79, 1, "WARNING: aio_write() returned error: " << xstrerror());
        /* fall back to blocking method */
        //       file_write(fd, offset, buf, len, callback, data, freefunc);
    }
}