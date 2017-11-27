static int wh_notify (notification_t const *n, user_data_t *ud) /* {{{ */
{
        wh_callback_t *cb;
        char alert[4096];
        int status;

        if ((ud == NULL) || (ud->data == NULL))
                return (EINVAL);

        cb = ud->data;
        assert (cb->send_notifications);

        status = format_json_notification (alert, sizeof (alert), n);
        if (status != 0)
        {
                ERROR ("write_http plugin: formatting notification failed");
                return status;
        }

        pthread_mutex_lock (&cb->send_lock);
        if (wh_callback_init (cb) != 0)
        {
                ERROR ("write_http plugin: wh_callback_init failed.");
                pthread_mutex_unlock (&cb->send_lock);
                return (-1);
        }

        status = wh_post_nolock (cb, alert);
        pthread_mutex_unlock (&cb->send_lock);

        return (status);
}