static int gr_format_values (char *ret, size_t ret_len,
        int ds_num, const data_set_t *ds, const value_list_t *vl,
        gauge_t const *rates)
{
    size_t offset = 0;
    int status;

    assert (0 == strcmp (ds->type, vl->type));

    memset (ret, 0, ret_len);

#define BUFFER_ADD(...) do { \
    status = ssnprintf (ret + offset, ret_len - offset, \
            __VA_ARGS__); \
    if (status < 1) \
    { \
        return (-1); \
    } \
    else if (((size_t) status) >= (ret_len - offset)) \
    { \
        return (-1); \
    } \
    else \
    offset += ((size_t) status); \
} while (0)

    if (ds->ds[ds_num].type == DS_TYPE_GAUGE)
        BUFFER_ADD (GAUGE_FORMAT, vl->values[ds_num].gauge);
    else if (rates != NULL)
        BUFFER_ADD ("%f", rates[ds_num]);
    else if (ds->ds[ds_num].type == DS_TYPE_COUNTER)
        BUFFER_ADD ("%llu", vl->values[ds_num].counter);
    else if (ds->ds[ds_num].type == DS_TYPE_DERIVE)
        BUFFER_ADD ("%"PRIi64, vl->values[ds_num].derive);
    else if (ds->ds[ds_num].type == DS_TYPE_ABSOLUTE)
        BUFFER_ADD ("%"PRIu64, vl->values[ds_num].absolute);
    else
    {
        ERROR ("gr_format_values plugin: Unknown data source type: %i",
                ds->ds[ds_num].type);
        return (-1);
    }

#undef BUFFER_ADD

    return (0);
}