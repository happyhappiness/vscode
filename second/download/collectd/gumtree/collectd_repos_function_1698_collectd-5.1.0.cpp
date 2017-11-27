static void wg_callback_free (void *data)
{
    struct wg_callback *cb;

    if (data == NULL)
        return;

    cb = data;

    pthread_mutex_lock (&cb->send_lock);

    wg_flush_nolock (/* timeout = */ 0, cb);

    close(cb->sock_fd);
    cb->sock_fd = -1;

    sfree(cb->node);
    sfree(cb->service);
    sfree(cb->prefix);
    sfree(cb->postfix);

    pthread_mutex_destroy (&cb->send_lock);

    sfree(cb);
}