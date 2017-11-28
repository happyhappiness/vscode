void
IdleConnList::removeFD(int fd)
{
    int index = findFDIndex(fd);
    if (index < 0) {
        debugs(48, 2, "IdleConnList::removeFD: FD " << fd << " NOT FOUND!");
        return;
    }
    debugs(48, 3, "IdleConnList::removeFD: found FD " << fd << " at index " << index);

    for (; index < nfds - 1; index++)
        fds[index] = fds[index + 1];

    if (--nfds == 0) {
        debugs(48, 3, "IdleConnList::removeFD: deleting " << hashKeyStr(&hash));
        delete this;
    }
}