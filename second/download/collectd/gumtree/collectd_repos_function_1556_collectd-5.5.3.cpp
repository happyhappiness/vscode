static uint32_t backup_search_for_type(struct ceph_daemon *d, char *ds_name)
{
    int idx = 0;
    for(; idx < d->ds_num; idx++)
    {
        if(strcmp(d->ds_names[idx], ds_name) == 0)
        {
            return d->ds_types[idx];
        }
    }
    return DSET_TYPE_UNFOUND;
}