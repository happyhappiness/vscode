static int wg_send_message (const char* key, const char* value,
        cdtime_t time, struct wg_callback *cb)
{
    int status;
    size_t message_len;
    char message[1024];

    message_len = (size_t) ssnprintf (message, sizeof (message),
            "%s %s %u\r\n",
            key,
            value,
            (unsigned int) CDTIME_T_TO_TIME_T (time));
    if (message_len >= sizeof (message)) {
        ERROR ("write_graphite plugin: message buffer too small: "
                "Need %zu bytes.", message_len + 1);
        return (-1);
    }

    pthread_mutex_lock (&cb->send_lock);

    if (cb->sock_fd < 0)
    {
        status = wg_callback_init (cb);
        if (status != 0)
        {
            ERROR ("write_graphite plugin: wg_callback_init failed.");
            pthread_mutex_unlock (&cb->send_lock);
            return (-1);
        }
    }

    if (message_len >= cb->send_buf_free)
    {
        status = wg_flush_nolock (/* timeout = */ 0, cb);
        if (status != 0)
        {
            pthread_mutex_unlock (&cb->send_lock);
            return (status);
        }
    }

    /* Assert that we have enough space for this message. */
    assert (message_len < cb->send_buf_free);

    /* `message_len + 1' because `message_len' does not include the
     * trailing null byte. Neither does `send_buffer_fill'. */
    memcpy (cb->send_buf + cb->send_buf_fill,
            message, message_len + 1);
    cb->send_buf_fill += message_len;
    cb->send_buf_free -= message_len;

    DEBUG ("write_graphite plugin: [%s]:%s buf %zu/%zu (%.1f %%) \"%s\"",
            cb->node,
            cb->service,
            cb->send_buf_fill, sizeof (cb->send_buf),
            100.0 * ((double) cb->send_buf_fill) / ((double) sizeof (cb->send_buf)),
            message);

    pthread_mutex_unlock (&cb->send_lock);

    return (0);
}