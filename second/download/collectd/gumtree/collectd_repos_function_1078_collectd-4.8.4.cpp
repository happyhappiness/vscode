static int wh_value_list_to_string (char *buffer, /* {{{ */
                size_t buffer_size,
                const data_set_t *ds, const value_list_t *vl)
{
        size_t offset = 0;
        int status;
        int i;

        assert (0 == strcmp (ds->type, vl->type));

        memset (buffer, 0, buffer_size);

#define BUFFER_ADD(...) do { \
        status = ssnprintf (buffer + offset, buffer_size - offset, \
                        __VA_ARGS__); \
        if (status < 1) \
                return (-1); \
        else if (((size_t) status) >= (buffer_size - offset)) \
                return (-1); \
        else \
                offset += ((size_t) status); \
} while (0)

        BUFFER_ADD ("%lu", (unsigned long) vl->time);

        for (i = 0; i < ds->ds_num; i++)
{
        if (ds->ds[i].type == DS_TYPE_GAUGE)
                BUFFER_ADD (":%f", vl->values[i].gauge);
        else if (ds->ds[i].type == DS_TYPE_COUNTER)
                BUFFER_ADD (":%llu", vl->values[i].counter);
        else if (ds->ds[i].type == DS_TYPE_DERIVE)
                BUFFER_ADD (":%"PRIi64, vl->values[i].derive);
        else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
                BUFFER_ADD (":%"PRIu64, vl->values[i].absolute);
        else
        {
                ERROR ("write_http plugin: Unknown data source type: %i",
                                ds->ds[i].type);
                return (-1);
        }
} /* for ds->ds_num */

#undef BUFFER_ADD

return (0);
}