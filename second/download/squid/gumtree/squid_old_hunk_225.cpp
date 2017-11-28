
        xfree(client);
    }
}

void
Ident::Close(int fdnotused, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    identCallback(state, NULL);
    comm_close(state->fd);
    hash_remove_link(ident_hash, (hash_link *) state);
    xfree(state->hash.key);
    cbdataFree(state);
}

void
Ident::Timeout(int fd, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    debugs(30, 3, "identTimeout: FD " << fd << ", " << state->my_peer);

    comm_close(fd);
}

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

void
Ident::ReadReply(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    char *ident = NULL;
    char *t = NULL;

    assert (buf == state->buf);

    if (flag != COMM_OK || len <= 0) {
        comm_close(fd);
        return;
    }

    /*
     * XXX This isn't really very tolerant. It should read until EOL
     * or EOF and then decode the answer... If the reply is fragmented
