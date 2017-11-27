static int wg_send_message (char const *message, struct wg_callback *cb)
{
    int status;
    size_t message_len;

    message_len = strlen (message);

    pthread_mutex_lock (&cb->send_lock);

    if (cb->sock_fd < 0)
    {
        status = wg_callback_init (cb);
        if (status != 0)
        {
            /* An error message has already been printed. */
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

    DEBUG ("write_graphite plugin: [%s]:%s (%s) buf %zu/%zu (%.1f %%) \"%s\"",
            cb->node,
            cb->service,
            cb->protocol,
            cb->send_buf_fill, sizeof (cb->send_buf),
            100.0 * ((double) cb->send_buf_fill) / ((double) sizeof (cb->send_buf)),
            message);

    pthread_mutex_unlock (&cb->send_lock);

    return (0);
}