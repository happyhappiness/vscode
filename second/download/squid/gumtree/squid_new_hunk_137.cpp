
    fs = (file_state *)xcalloc(1, sizeof(*fs));
    fs->id = r->id;
    fs->key = &fs->id;		/* gack */
    fs->fd = fd;
    hash_join(hash, (hash_link *) fs);
    DEBUG(2) {
        fprintf(stderr, "%d OPEN  id %d, FD %d, fs %p\n",
                (int) mypid,
                fs->id,
                fs->fd,
                fs);
    }
    return fd;
}

static int
do_close(diomsg * r, int len)
{
