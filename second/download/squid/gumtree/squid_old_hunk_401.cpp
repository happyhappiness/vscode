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
