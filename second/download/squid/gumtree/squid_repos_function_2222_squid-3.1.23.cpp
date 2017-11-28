static void
idnsDoSendQueryVC(nsvc *vc)
{
    if (vc->busy)
        return;

    if (vc->queue->contentSize() == 0)
        return;

    MemBuf *mb = vc->queue;

    vc->queue = new MemBuf;

    vc->busy = 1;

    commSetTimeout(vc->fd, Config.Timeout.idns_query, NULL, NULL);

    comm_write_mbuf(vc->fd, mb, idnsSentQueryVC, vc);

    delete mb;
}