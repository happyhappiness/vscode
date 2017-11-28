void
file_write(int fd,
           off_t file_offset,
           void const *ptr_to_buf,
           int len,
           DWCB * handle,
           void *handle_data,
           FREE * free_func)
{
    dwrite_q *wq = NULL;
    fde *F = &fd_table[fd];
    PROF_start(file_write);
    assert(fd >= 0);
    assert(F->flags.open);
    /* if we got here. Caller is eligible to write. */
    wq = (dwrite_q *)memAllocate(MEM_DWRITE_Q);
    wq->file_offset = file_offset;
    wq->buf = (char *)ptr_to_buf;
    wq->len = len;
    wq->buf_offset = 0;
    wq->next = NULL;
    wq->free_func = free_func;

    if (!F->disk.wrt_handle_data) {
        F->disk.wrt_handle = handle;
        F->disk.wrt_handle_data = cbdataReference(handle_data);
    } else {
        /* Detect if there is multiple concurrent users of this fd.. we only support one callback */
        assert(F->disk.wrt_handle_data == handle_data && F->disk.wrt_handle == handle);
    }

    /* add to queue */
    if (F->disk.write_q == NULL) {
        /* empty queue */
        F->disk.write_q = F->disk.write_q_tail = wq;
    } else {
        F->disk.write_q_tail->next = wq;
        F->disk.write_q_tail = wq;
    }

    if (!F->flags.write_daemon) {
        diskHandleWrite(fd, NULL);
    }

    PROF_stop(file_write);
}