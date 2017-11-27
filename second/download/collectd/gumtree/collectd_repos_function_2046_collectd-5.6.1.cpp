static int wg_flush_nolock (cdtime_t timeout, struct wg_callback *cb)
{
    int status;

    DEBUG ("write_graphite plugin: wg_flush_nolock: timeout = %.3f; "
            "send_buf_fill = %zu;",
            (double)timeout,
            cb->send_buf_fill);

    /* timeout == 0  => flush unconditionally */
    if (timeout > 0)
    {
        cdtime_t now;

        now = cdtime ();
        if ((cb->send_buf_init_time + timeout) > now)
            return (0);
    }

    if (cb->send_buf_fill == 0)
    {
        cb->send_buf_init_time = cdtime ();
        return (0);
    }

    status = wg_send_buffer (cb);
    wg_reset_buffer (cb);

    return (status);
}