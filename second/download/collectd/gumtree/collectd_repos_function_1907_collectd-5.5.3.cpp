static int wg_send_buffer (struct wg_callback *cb)
{
    ssize_t status = 0;

    status = swrite (cb->sock_fd, cb->send_buf, strlen (cb->send_buf));
    if (status != 0)
    {
        const char *protocol = cb->protocol ? cb->protocol : WG_DEFAULT_PROTOCOL;

        if (cb->log_send_errors)
        {
            char errbuf[1024];
            ERROR ("write_graphite plugin: send to %s:%s (%s) failed with status %zi (%s)",
                    cb->node, cb->service, protocol,
                    status, sstrerror (errno, errbuf, sizeof (errbuf)));
        }

        close (cb->sock_fd);
        cb->sock_fd = -1;

        return (-1);
    }

    return (0);
}