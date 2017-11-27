static int wt_write(const data_set_t *ds, const value_list_t *vl,
                    user_data_t *user_data)
{
    struct wt_callback *cb;
    int status;

    if (user_data == NULL)
        return EINVAL;

    cb = user_data->data;

    status = wt_write_messages(ds, vl, cb);

    return status;
}