void
Ident::ConnectDone(int fd, const DnsLookupDetails &, comm_err_t status, int xerrno, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    IdentClient *c;

    if (status != COMM_OK) {
        /* Failed to connect */
        comm_close(fd);
        return;
    }

    /*
     * see if any of our clients still care
     */
    for (c = state->clients; c; c = c->next) {
        if (cbdataReferenceValid(c->callback_data))
            break;
    }

    if (c == NULL) {
        /* no clients care */
        comm_close(fd);
        return;
    }

    MemBuf mb;
    mb.init();
    mb.Printf("%d, %d\r\n",
              state->my_peer.GetPort(),
              state->me.GetPort());
    comm_write_mbuf(fd, &mb, NULL, state);
    comm_read(fd, state->buf, BUFSIZ, Ident::ReadReply, state);
    commSetTimeout(fd, Ident::TheConfig.timeout, Ident::Timeout, state);
}