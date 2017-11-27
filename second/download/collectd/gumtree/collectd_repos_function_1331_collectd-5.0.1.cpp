static int wh_write (const data_set_t *ds, const value_list_t *vl, /* {{{ */
                user_data_t *user_data)
{
        wh_callback_t *cb;
        int status;

        if (user_data == NULL)
                return (-EINVAL);

        cb = user_data->data;

        if (cb->format == WH_FORMAT_JSON)
                status = wh_write_json (ds, vl, cb);
        else
                status = wh_write_command (ds, vl, cb);

        return (status);
}