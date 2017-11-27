static int wg_write (const data_set_t *ds, const value_list_t *vl,
        user_data_t *user_data)
{
    struct wg_callback *cb;
    int status;

    if (user_data == NULL)
        return (EINVAL);

    cb = user_data->data;

    status = wg_write_messages (ds, vl, cb);

    return (status);
}