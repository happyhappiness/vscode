
    fs->offset = r->offset + x;
    return x;
}

static int
do_unlink(diomsg * r, int len, const char *buf)
{
    if (unlink(buf) < 0) {
        DEBUG(1) {
            fprintf(stderr, "%d UNLNK id %d %s: ", (int) mypid, r->id, buf);
            perror("unlink");
        }
