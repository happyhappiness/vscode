static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
    aeApiState *state = eventLoop->apidata;
    struct timespec timeout, *tsp;
    int mask;
    port_event_t event;

    /*
     * If we've returned an fd event before, we must reassociated that fd with
     * the port now, before calling port_get().  See the block comment at the
     * top of this file for an explanation of why.
     */
    if (state->pending_mask != AE_NONE) {
        if (aeApiAssociate("aeApiPoll", state->portfd, state->pending_fd,
            state->pending_mask) != 0) {
            /* See aeApiDelEvent for why this case is fatal. */
            abort();
        }

        state->pending_mask = AE_NONE;
        state->pending_fd = -1;
    }

    if (tvp != NULL) {
        timeout.tv_sec = tvp->tv_sec;
        timeout.tv_nsec = tvp->tv_usec * 1000;
        tsp = &timeout;
    } else {
        tsp = NULL;
    }

    if (port_get(state->portfd, &event, tsp) == -1) {
        if (errno == ETIME || errno == EINTR)
            return 0;

        /* Any other error indicates a bug. */
        perror("aeApiPoll: port_get");
        abort();
    }

    mask = 0;
    if (event.portev_events & POLLIN)
        mask |= AE_READABLE;
    if (event.portev_events & POLLOUT)
        mask |= AE_WRITABLE;

    eventLoop->fired[0].fd = event.portev_object;
    eventLoop->fired[0].mask = mask;

    if (evport_debug)
        fprintf(stderr, "aeApiPoll: fd %d mask 0x%x\n", event.portev_object,
            mask);

    state->pending_fd = event.portev_object;
    state->pending_mask = (uintptr_t)event.portev_user;

    return 1;
}