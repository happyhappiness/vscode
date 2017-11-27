static int wh_write (const data_set_t *ds, const value_list_t *vl, /* {{{ */
                user_data_t *user_data)
{
        wh_callback_t *cb;
        int status;

        if (user_data == NULL)
                return (-EINVAL);

        cb = user_data->data;
        assert (cb->send_metrics);

        switch(cb->format) {
            case WH_FORMAT_JSON:
                status = wh_write_json (ds, vl, cb);
                break;
            case WH_FORMAT_KAIROSDB:
                status = wh_write_kairosdb (ds, vl, cb);
                break;
            default:
                status = wh_write_command (ds, vl, cb);
                break;
        }
        return (status);
}