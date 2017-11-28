void
IdleConnList::read(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    debugs(48, 3, "IdleConnList::read: " << len << " bytes from FD " << fd);

    if (flag == COMM_ERR_CLOSING) {
        /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */
        return;
    }

    IdleConnList *list = (IdleConnList *) data;
    list->removeFD(fd);	/* might delete list */
    comm_close(fd);
}