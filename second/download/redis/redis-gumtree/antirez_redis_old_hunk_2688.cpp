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

static char *aeApiName(void) {
