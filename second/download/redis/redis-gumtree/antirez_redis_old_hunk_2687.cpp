
static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int mask) {
    aeApiState *state = eventLoop->apidata;
    int fullmask;

    if (evport_debug)
        fprintf(stderr, "del fd %d mask 0x%x\n", fd, mask);

    if (fd == state->pending_fd) {
        if (evport_debug)
            fprintf(stderr, "deleting event from pending fd %d\n", fd);

