static int
do_open(diomsg * r, int len, const char *buf)
{
    int fd;
    file_state *fs;
    /*
     * note r->offset holds open() flags
     */
    fd = open(buf, r->offset, 0600);

    if (fd < 0) {
        DEBUG(1) {
            fprintf(stderr, "%d %s: ", (int) mypid, buf);
            perror("open");
        }

        return -errno;
    }

    fs = (file_state *)xcalloc(1, sizeof(*fs));
    fs->id = r->id;
    fs->key = &fs->id;          /* gack */
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