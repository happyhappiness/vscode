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
