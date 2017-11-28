static void
helperDispatchWriteDone(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    helper_server *srv = (helper_server *)data;

    srv->writebuf->clean();
    delete srv->writebuf;
    srv->writebuf = NULL;
    srv->flags.writing = 0;

    if (flag != COMM_OK) {
        /* Helper server has crashed */
        debugs(84, 0, "helperDispatch: Helper " << srv->parent->id_name << " #" << srv->index + 1 << " has crashed");
        return;
    }

    if (!srv->wqueue->isNull()) {
        srv->writebuf = srv->wqueue;
        srv->wqueue = new MemBuf;
        srv->flags.writing = 1;
        comm_write(srv->wfd,
                   srv->writebuf->content(),
                   srv->writebuf->contentSize(),
                   helperDispatchWriteDone,	/* Handler */
                   srv, NULL);			/* Handler-data, freefunc */
    }
}