static int wg_write_messages (const data_set_t *ds, const value_list_t *vl,
        struct wg_callback *cb)
{
    char buffer[WG_SEND_BUF_SIZE] = { 0 };
    int status;

    if (0 != strcmp (ds->type, vl->type))
    {
        ERROR ("write_graphite plugin: DS type does not match "
                "value list type");
        return -1;
    }

    status = format_graphite (buffer, sizeof (buffer), ds, vl,
            cb->prefix, cb->postfix, cb->escape_char, cb->format_flags);
    if (status != 0) /* error message has been printed already. */
        return (status);

    /* Send the message to graphite */
    status = wg_send_message (buffer, cb);
    if (status != 0) /* error message has been printed already. */
        return (status);

    return (0);
}