static int riemann_batch_add_value_list (struct riemann_host *host, /* {{{ */
                                         data_set_t const *ds,
                                         value_list_t const *vl,
                                         int *statuses)
{
	size_t i;
    Event **events;
    Msg *msg;
    size_t len;
    int ret;

    msg = riemann_value_list_to_protobuf (host, ds, vl, statuses);
    if (msg == NULL)
        return -1;

    pthread_mutex_lock(&host->lock);

    if (host->batch_msg == NULL) {
        host->batch_msg = msg;
    } else {
        len = msg->n_events + host->batch_msg->n_events;
        events = realloc(host->batch_msg->events,
                         (len * sizeof(*host->batch_msg->events)));
        if (events == NULL) {
            pthread_mutex_unlock(&host->lock);
            ERROR ("write_riemann plugin: out of memory");
            riemann_msg_protobuf_free (msg);
            return -1;
        }
        host->batch_msg->events = events;

        for (i = host->batch_msg->n_events; i < len; i++)
            host->batch_msg->events[i] = msg->events[i - host->batch_msg->n_events];

        host->batch_msg->n_events = len;
        sfree (msg->events);
        msg->n_events = 0;
        sfree (msg);
    }

	len = msg__get_packed_size(host->batch_msg);
    ret = 0;
    if (len >= host->batch_max) {
        ret = riemann_batch_flush_nolock(0, host);
    }

    pthread_mutex_unlock(&host->lock);
    return ret;
}