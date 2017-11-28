int
IdleConnList::findFDIndex (int fd)
{
    int index;

    for (index = nfds - 1; index >= 0; --index) {
        if (fds[index] == fd)
            return index;
    }

    return -1;
}