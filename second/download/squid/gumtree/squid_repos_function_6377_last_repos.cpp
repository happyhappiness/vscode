static int
do_read(diomsg * r, int, char *buf)
{
    int x;
    int readlen = r->size;
    file_state *fs;
    fs = (file_state *) hash_lookup(hash, &r->id);

    if (NULL == fs) {
        errno = EBADF;
        DEBUG(1) {
            fprintf(stderr, "%d READ  id %d: ", (int) mypid, r->id);
            perror("do_read");
        }

        return -errno;
    }

    if (r->offset > -1 && r->offset != fs->offset) {
        DEBUG(2) {
            fprintf(stderr, "seeking to %" PRId64 "\n", (int64_t)r->offset);
        }

        if (lseek(fs->fd, r->offset, SEEK_SET) < 0) {
            DEBUG(1) {
                fprintf(stderr, "%d FD %d, offset %" PRId64 ": ", (int) mypid, fs->fd, (int64_t)r->offset);
                perror("lseek");
            }
        }
    }

    x = read(fs->fd, buf, readlen);
    DEBUG(2) {
        fprintf(stderr, "%d READ %d,%d,%" PRId64 " ret %d\n", (int) mypid,
                fs->fd, readlen, (int64_t)r->offset, x);
    }

    if (x < 0) {
        DEBUG(1) {
            fprintf(stderr, "%d FD %d: ", (int) mypid, fs->fd);
            perror("read");
        }

        return -errno;
    }

    fs->offset = r->offset + x;
    return x;
}