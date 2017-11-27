int format_graphite (char *buffer, size_t buffer_size,
    data_set_t const *ds, value_list_t const *vl,
    char const *prefix, char const *postfix, char const escape_char,
    unsigned int flags)
{
    int status = 0;
    int i;
    int buffer_pos = 0;

    gauge_t *rates = NULL;
    if (flags & GRAPHITE_STORE_RATES)
      rates = uc_get_rate (ds, vl);

    for (i = 0; i < ds->ds_num; i++)
    {
        char const *ds_name = NULL;
        char        key[10*DATA_MAX_NAME_LEN];
        char        values[512];
        size_t      message_len;
        char        message[1024];

        if ((flags & GRAPHITE_ALWAYS_APPEND_DS)
            || (ds->ds_num > 1))
          ds_name = ds->ds[i].name;

        /* Copy the identifier to `key' and escape it. */
        status = gr_format_name (key, sizeof (key), vl, ds_name,
                    prefix, postfix, escape_char, flags);
        if (status != 0)
        {
            ERROR ("format_graphite: error with gr_format_name");
            sfree (rates);
            return (status);
        }

        escape_graphite_string (key, escape_char);
        /* Convert the values to an ASCII representation and put that into
         * `values'. */
        status = gr_format_values (values, sizeof (values), i, ds, vl, rates);
        if (status != 0)
        {
            ERROR ("format_graphite: error with gr_format_values");
            sfree (rates);
            return (status);
        }

        /* Compute the graphite command */
        message_len = (size_t) ssnprintf (message, sizeof (message),
                "%s %s %u\r\n",
                key,
                values,
                (unsigned int) CDTIME_T_TO_TIME_T (vl->time));
        if (message_len >= sizeof (message)) {
            ERROR ("format_graphite: message buffer too small: "
                    "Need %zu bytes.", message_len + 1);
            sfree (rates);
            return (-ENOMEM);
        }

        /* Append it in case we got multiple data set */
        if ((buffer_pos + message_len) >= buffer_size)
        {
            ERROR ("format_graphite: target buffer too small");
            sfree (rates);
            return (-ENOMEM);
        }
        memcpy((void *) (buffer + buffer_pos), message, message_len);
        buffer_pos += message_len;
        buffer[buffer_pos] = '\0';
    }
    sfree (rates);
    return (status);
}