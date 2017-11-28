    s->offset = 0;		/* optional, debugging */
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
