static int tcsv_read_metric (instance_definition_t *id,
        metric_definition_t *md,
        char **fields, size_t fields_num)
{
    value_t v;
    cdtime_t t;
    int status;

    if (md->data_source_type == -1)
        return (EINVAL);

    if (md->value_from >= fields_num)
        return (EINVAL);

    if (id->time_from >= 0 && (id->time_from >= fields_num))
        return (EINVAL);

    t = 0;
    if (id->time_from >= 0)
        t = parse_time (fields[id->time_from]);

    status = parse_value (fields[md->value_from], &v, md->data_source_type);
    if (status != 0)
        return (status);

    return (tcsv_submit (id, md, v, t));
}