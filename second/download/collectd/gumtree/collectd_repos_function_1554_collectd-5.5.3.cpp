static int backup_search_for_last_avg(struct ceph_daemon *d, const char *ds_n)
{
    int i = 0;
    for(; i < d->last_idx; i++)
    {
        if(strcmp(d->last_poll_data[i]->ds_name, ds_n) == 0)
        {
            return i;
        }
    }
    return -1;
}