static void
msg_handle(diomsg * r, int rl, diomsg * s)
{
    char *buf = NULL;
    s->mtype = r->mtype;
    s->id = r->id;
    s->seq_no = r->seq_no;      /* optional, debugging */
    s->callback_data = r->callback_data;
    s->requestor = r->requestor;
    s->size = 0;                /* optional, debugging */
    s->offset = 0;              /* optional, debugging */
    s->shm_offset = r->shm_offset;
    s->newstyle = r->newstyle;

    if (s->shm_offset > -1)
        buf = shmbuf + s->shm_offset;
    else if (r->mtype != _MQD_CLOSE) {
        fprintf(stderr, "%d UNLNK id(%u) Error: no filename in shm buffer\n", (int) mypid, s->id);
        return;
    }

    switch (r->mtype) {

    case _MQD_OPEN:

    case _MQD_CREATE:
        s->status = do_open(r, rl, buf);
        break;

    case _MQD_CLOSE:
        s->status = do_close(r, rl);
        break;

    case _MQD_READ:
        s->status = do_read(r, rl, buf);
        break;

    case _MQD_WRITE:
        s->status = do_write(r, rl, buf);
        break;

    case _MQD_UNLINK:
        s->status = do_unlink(r, rl, buf);
        break;

    default:
        assert(0);
        break;
    }
}