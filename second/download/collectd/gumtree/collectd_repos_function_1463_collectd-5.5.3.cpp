static int riemann_batch_flush_nolock (cdtime_t timeout,
                                       struct riemann_host *host)
{
    cdtime_t    now;
    int         status = 0;

    if (timeout > 0) {
        now = cdtime ();
        if ((host->batch_init + timeout) > now)
            return status;
    }
    riemann_send_msg(host, host->batch_msg);
    riemann_msg_protobuf_free(host->batch_msg);

	if (host->use_tcp && ((status = riemann_recv_ack(host)) != 0))
        riemann_disconnect (host);

    host->batch_init = cdtime();
    host->batch_msg = NULL;
    return status;
}