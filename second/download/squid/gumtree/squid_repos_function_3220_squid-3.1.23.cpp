int
IdleConnList::findUseableFD()
{
    assert(nfds);

    for (int i=nfds-1; i>=0; i--) {
        if (!comm_has_pending_read_callback(fds[i])) {
            return fds[i];
        }
    }

    return -1;
}