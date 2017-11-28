static void
diskHandleWrite(int fd, void *notused)
{
    int len = 0;
    fde *F = &fd_table[fd];

    struct _fde_disk *fdd = &F->disk;
    dwrite_q *q = fdd->write_q;
    int status = DISK_OK;
    int do_close;

    if (NULL == q)
        return;

    PROF_start(diskHandleWrite);

    debugs(6, 3, "diskHandleWrite: FD " << fd);

    F->flags.write_daemon = 0;

    assert(fdd->write_q != NULL);

    assert(fdd->write_q->len > fdd->write_q->buf_offset);

    debugs(6, 3, "diskHandleWrite: FD " << fd << " writing " << (fdd->write_q->len - fdd->write_q->buf_offset) << " bytes");

    errno = 0;

    if (fdd->write_q->file_offset != -1)
        lseek(fd, fdd->write_q->file_offset, SEEK_SET);

    len = FD_WRITE_METHOD(fd,
                          fdd->write_q->buf + fdd->write_q->buf_offset,
                          fdd->write_q->len - fdd->write_q->buf_offset);

    debugs(6, 3, "diskHandleWrite: FD " << fd << " len = " << len);

    statCounter.syscalls.disk.writes++;

    fd_bytes(fd, len, FD_WRITE);

    if (len < 0) {
        if (!ignoreErrno(errno)) {
            status = errno == ENOSPC ? DISK_NO_SPACE_LEFT : DISK_ERROR;
            debugs(50, 1, "diskHandleWrite: FD " << fd << ": disk write error: " << xstrerror());

            /*
             * If there is no write callback, then this file is
             * most likely something important like a log file, or
             * an interprocess pipe.  Its not a swapfile.  We feel
             * that a write failure on a log file is rather important,
             * and Squid doesn't otherwise deal with this condition.
             * So to get the administrators attention, we exit with
             * a fatal message.
             */

            if (fdd->wrt_handle == NULL)
                fatal("Write failure -- check your disk space and cache.log");

            /*
             * If there is a write failure, then we notify the
             * upper layer via the callback, at the end of this
             * function.  Meanwhile, flush all pending buffers
             * here.  Let the upper layer decide how to handle the
             * failure.  This will prevent experiencing multiple,
             * repeated write failures for the same FD because of
             * the queued data.
             */
            do {
                fdd->write_q = q->next;

                if (q->free_func)
                    (q->free_func) (q->buf);

                if (q) {
                    memFree(q, MEM_DWRITE_Q);
                    q = NULL;
                }
            } while ((q = fdd->write_q));
        }

        len = 0;
    }

    if (q != NULL) {
        /* q might become NULL from write failure above */
        q->buf_offset += len;

        if (q->buf_offset > q->len)
            debugs(50, 1, "diskHandleWriteComplete: q->buf_offset > q->len (" <<
                   q << "," << (int) q->buf_offset << ", " << q->len << ", " <<
                   len << " FD " << fd << ")");


        assert(q->buf_offset <= q->len);

        if (q->buf_offset == q->len) {
            /* complete write */
            fdd->write_q = q->next;

            if (q->free_func)
                (q->free_func) (q->buf);

            if (q) {
                memFree(q, MEM_DWRITE_Q);
                q = NULL;
            }
        }
    }

    if (fdd->write_q == NULL) {
        /* no more data */
        fdd->write_q_tail = NULL;
    } else {
        /* another block is queued */
        diskCombineWrites(fdd);
        commSetSelect(fd, COMM_SELECT_WRITE, diskHandleWrite, NULL, 0);
        F->flags.write_daemon = 1;
    }

    do_close = F->flags.close_request;

    if (fdd->wrt_handle) {
        DWCB *callback = fdd->wrt_handle;
        void *cbdata;
        fdd->wrt_handle = NULL;

        if (cbdataReferenceValidDone(fdd->wrt_handle_data, &cbdata)) {
            callback(fd, status, len, cbdata);
            /*
             * NOTE, this callback can close the FD, so we must
             * not touch 'F', 'fdd', etc. after this.
             */
            PROF_stop(diskHandleWrite);
            return;
            /* XXX But what about close_request??? */
        }
    }

    if (do_close)
        file_close(fd);

    PROF_stop(diskHandleWrite);
}