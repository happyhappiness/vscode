static int
do_close(diomsg * r, int)
{
    int fd;
    file_state *fs;
    fs = (file_state *) hash_lookup(hash, &r->id);

    if (NULL == fs) {
        errno = EBADF;
        DEBUG(1) {
            fprintf(stderr, "%d CLOSE id %d: ", (int) mypid, r->id);
            perror("do_close");
        }

        return -errno;
    }

    fd = fs->fd;
    hash_remove_link(hash, (hash_link *) fs);
    DEBUG(2) {
        fprintf(stderr, "%d CLOSE id %d, FD %d, fs %p\n",
                (int) mypid,
                r->id,
                fs->fd,
                fs);
    }
    xfree(fs);
    return close(fd);
}