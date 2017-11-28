void
IdleConnList::push(int fd)
{
    if (nfds == nfds_alloc) {
        debugs(48, 3, "IdleConnList::push: growing FD array");
        nfds_alloc <<= 1;
        int *old = fds;
        fds = (int *)xmalloc(nfds_alloc * sizeof(int));
        xmemcpy(fds, old, nfds * sizeof(int));

        if (nfds == PCONN_FDS_SZ)
            pconn_fds_pool->free(old);
        else
            xfree(old);
    }

    fds[nfds++] = fd;
    comm_read(fd, fakeReadBuf, sizeof(fakeReadBuf), IdleConnList::read, this);
    commSetTimeout(fd, Config.Timeout.pconn, IdleConnList::timeout, this);
}