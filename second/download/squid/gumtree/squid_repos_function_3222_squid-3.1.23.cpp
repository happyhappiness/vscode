void
IdleConnList::timeout(int fd, void *data)
{
    debugs(48, 3, "IdleConnList::timeout: FD " << fd);
    IdleConnList *list = (IdleConnList *) data;
    list->removeFD(fd);	/* might delete list */
    comm_close(fd);
}