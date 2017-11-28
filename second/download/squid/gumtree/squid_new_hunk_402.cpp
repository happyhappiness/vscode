    /* Account */
    ++strategy->aq.aq_numpending;

    /* Initiate aio */
    if (aio_write(&qe->aq_e_aiocb) < 0) {
        fatalf("Aiee! aio_write() returned error (%d) FIXME and wrap file_write !\n", errno);
        debugs(79, DBG_IMPORTANT, "WARNING: aio_write() returned error: " << xstrerror());
        /* fall back to blocking method */
        //       file_write(fd, offset, buf, len, callback, data, freefunc);
    }
}

void
