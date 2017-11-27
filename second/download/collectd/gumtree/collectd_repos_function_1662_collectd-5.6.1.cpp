static uint32_t backup_search_for_type(struct ceph_daemon *d, char *ds_name)
{
    for(int i = 0; i < d->ds_num; i++)
    {
        if(strcmp(d->ds_names[i], ds_name) == 0)
        {
            return d->ds_types[i];
        }
    }
    return DSET_TYPE_UNFOUND;
}