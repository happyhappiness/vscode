void
AIODiskFile::read(ReadRequest *request)
{
    int slot;
    async_queue_entry_t *qe;

    assert(strategy->aq.aq_state == AQ_STATE_SETUP);

    /* Find a free slot */
    slot = strategy->findSlot();

    if (slot < 0) {
        /* No free slot? Callback error, and return */
        fatal("Aiee! out of aiocb slots! - FIXME and wrap file_read\n");
        debugs(79, DBG_IMPORTANT, "WARNING: out of aiocb slots!");
        /* fall back to blocking method */
        //        file_read(fd, request->buf, request->len, request->offset, callback, data);
        return;
    }

    /* Mark slot as ours */
    qe = &strategy->aq.aq_queue[slot];

    qe->aq_e_state = AQ_ENTRY_USED;

    qe->aq_e_callback_data = cbdataReference(request);

    qe->theFile = cbdataReference(this);

    qe->aq_e_type = AQ_ENTRY_READ;

    qe->aq_e_free = NULL;

    qe->aq_e_buf =  request->buf;

    qe->aq_e_fd = getFD();

    qe->aq_e_aiocb.aio_fildes = getFD();

    qe->aq_e_aiocb.aio_nbytes = request->len;

    qe->aq_e_aiocb.aio_offset =  request->offset;

    qe->aq_e_aiocb.aio_buf =  request->buf;

    /* Account */
    ++ strategy->aq.aq_numpending;

    /* Initiate aio */
    if (aio_read(&qe->aq_e_aiocb) < 0) {
        fatalf("Aiee! aio_read() returned error (%d)  FIXME and wrap file_read !\n", errno);
        debugs(79, DBG_IMPORTANT, "WARNING: aio_read() returned error: " << xstrerror());
        /* fall back to blocking method */
        //        file_read(fd, request->buf, request->len, request->offset, callback, data);
    }

}