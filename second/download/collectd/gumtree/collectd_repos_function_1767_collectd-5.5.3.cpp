static int wl_write (const data_set_t *ds, const value_list_t *vl,
        user_data_t *user_data)
{
    int status;

    status = wl_write_messages (ds, vl);

    return (status);
}