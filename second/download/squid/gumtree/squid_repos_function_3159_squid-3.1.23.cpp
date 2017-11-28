static void
gopherReadReply(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;
    StoreEntry *entry = gopherState->entry;
    int clen;
    int bin;
    size_t read_sz = BUFSIZ;
    int do_next_read = 0;
#if DELAY_POOLS

    DelayId delayId = entry->mem_obj->mostBytesAllowed();
#endif

    /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */

    if (flag == COMM_ERR_CLOSING) {
        return;
    }

    assert(buf == gopherState->replybuf);

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        comm_close(fd);
        return;
    }

    errno = 0;
#if DELAY_POOLS

    read_sz = delayId.bytesWanted(1, read_sz);
#endif

    /* leave one space for \0 in gopherToHTML */

    if (flag == COMM_OK && len > 0) {
#if DELAY_POOLS
        delayId.bytesIn(len);
#endif

        kb_incr(&statCounter.server.all.kbytes_in, len);
        kb_incr(&statCounter.server.other.kbytes_in, len);
    }

    debugs(10, 5, "gopherReadReply: FD " << fd << " read len=" << len);

    if (flag == COMM_OK && len > 0) {
        commSetTimeout(fd, Config.Timeout.read, NULL, NULL);
        IOStats.Gopher.reads++;

        for (clen = len - 1, bin = 0; clen; bin++)
            clen >>= 1;

        IOStats.Gopher.read_hist[bin]++;
    }

    if (flag != COMM_OK || len < 0) {
        debugs(50, 1, "gopherReadReply: error reading: " << xstrerror());

        if (ignoreErrno(errno)) {
            do_next_read = 1;
        } else {
            ErrorState *err;
            err = errorCon(ERR_READ_ERROR, HTTP_INTERNAL_SERVER_ERROR, gopherState->fwd->request);
            err->xerrno = errno;
            gopherState->fwd->fail(err);
            comm_close(fd);
            do_next_read = 0;
        }
    } else if (len == 0 && entry->isEmpty()) {
        gopherState->fwd->fail(errorCon(ERR_ZERO_SIZE_OBJECT, HTTP_SERVICE_UNAVAILABLE, gopherState->fwd->request));
        comm_close(fd);
        do_next_read = 0;
    } else if (len == 0) {
        /* Connection closed; retrieval done. */
        /* flush the rest of data in temp buf if there is one. */

        if (gopherState->conversion != gopher_ds::NORMAL)
            gopherEndHTML(gopherState);

        entry->timestampsSet();

        entry->flush();

        gopherState->fwd->complete();

        comm_close(fd);

        do_next_read = 0;
    } else {
        if (gopherState->conversion != gopher_ds::NORMAL) {
            gopherToHTML(gopherState, buf, len);
        } else {
            entry->append(buf, len);
        }

        do_next_read = 1;
    }

    if (do_next_read)
        comm_read(fd, buf, read_sz, gopherReadReply, gopherState);

    return;
}