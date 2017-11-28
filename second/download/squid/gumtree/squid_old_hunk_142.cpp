    s->offset = 0;		/* optional, debugging */
    s->shm_offset = r->shm_offset;
    s->newstyle = r->newstyle;

    if (s->shm_offset > -1)
        buf = shmbuf + s->shm_offset;

    switch (r->mtype) {

    case _MQD_OPEN:

    case _MQD_CREATE:
