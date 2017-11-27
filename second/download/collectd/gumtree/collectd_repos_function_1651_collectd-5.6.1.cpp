static int ceph_daemon_add_ds_entry(struct ceph_daemon *d, const char *name,
        int pc_type)
{
    uint32_t type;
    char ds_name[DATA_MAX_NAME_LEN];

    if(convert_special_metrics)
    {
        /**
         * Special case for filestore:JournalWrBytes. For some reason, Ceph
         * schema encodes this as a count/sum pair while all other "Bytes" data
         * (excluding used/capacity bytes for OSD space) uses a single "Derive"
         * type. To spare further confusion, keep this KPI as the same type of
         * other "Bytes". Instead of keeping an "average" or "rate", use the
         * "sum" in the pair and assign that to the derive value.
         */
        if((strcmp(name,"filestore.journal_wr_bytes.type") == 0))
        {
            pc_type = 10;
        }
    }

    d->ds_names = realloc(d->ds_names, sizeof(char *) * (d->ds_num + 1));
    if(!d->ds_names)
    {
        return -ENOMEM;
    }

    d->ds_types = realloc(d->ds_types, sizeof(uint32_t) * (d->ds_num + 1));
    if(!d->ds_types)
    {
        return -ENOMEM;
    }

    d->ds_names[d->ds_num] = malloc(DATA_MAX_NAME_LEN);
    if(!d->ds_names[d->ds_num])
    {
        return -ENOMEM;
    }

    type = (pc_type & PERFCOUNTER_DERIVE) ? DSET_RATE :
            ((pc_type & PERFCOUNTER_LATENCY) ? DSET_LATENCY : DSET_BYTES);
    d->ds_types[d->ds_num] = type;

    if (parse_keys(ds_name, sizeof (ds_name), name))
    {
        return 1;
    }

    sstrncpy(d->ds_names[d->ds_num], ds_name, DATA_MAX_NAME_LEN -1);
    d->ds_num = (d->ds_num + 1);

    return 0;
}