static void

diskCombineWrites(struct _fde_disk *fdd)
{
    int len = 0;
    dwrite_q *q = NULL;
    dwrite_q *wq = NULL;
    /*
     * We need to combine multiple write requests on an FD's write
     * queue But only if we don't need to seek() in between them, ugh!
     * XXX This currently ignores any seeks (file_offset)
     */

    if (fdd->write_q != NULL && fdd->write_q->next != NULL) {
        len = 0;

        for (q = fdd->write_q; q != NULL; q = q->next)
            len += q->len - q->buf_offset;

        wq = (dwrite_q *)memAllocate(MEM_DWRITE_Q);

        wq->buf = (char *)xmalloc(len);

        wq->len = 0;

        wq->buf_offset = 0;

        wq->next = NULL;

        wq->free_func = xfree;

        do {
            q = fdd->write_q;
            len = q->len - q->buf_offset;
            xmemcpy(wq->buf + wq->len, q->buf + q->buf_offset, len);
            wq->len += len;
            fdd->write_q = q->next;

            if (q->free_func)
                (q->free_func) (q->buf);

            if (q) {
                memFree(q, MEM_DWRITE_Q);
                q = NULL;
            }
        } while (fdd->write_q != NULL);

        fdd->write_q_tail = wq;

        fdd->write_q = wq;
    }
}