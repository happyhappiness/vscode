static int add_last(struct ceph_daemon *d, const char *ds_n, double cur_sum,
        uint64_t cur_count)
{
    d->last_poll_data[d->last_idx] = malloc(1 * sizeof(struct last_data));
    if(!d->last_poll_data[d->last_idx])
    {
        return -ENOMEM;
    }
    sstrncpy(d->last_poll_data[d->last_idx]->ds_name,ds_n,
            sizeof(d->last_poll_data[d->last_idx]->ds_name));
    d->last_poll_data[d->last_idx]->last_sum = cur_sum;
    d->last_poll_data[d->last_idx]->last_count = cur_count;
    d->last_idx = (d->last_idx + 1);
    return 0;
}