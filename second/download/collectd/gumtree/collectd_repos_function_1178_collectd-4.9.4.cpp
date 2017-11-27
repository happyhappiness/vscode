static int wh_flush_nolock (int timeout, wh_callback_t *cb) /* {{{ */
{
        int status;

        DEBUG ("write_http plugin: wh_flush_nolock: timeout = %i; "
                        "send_buffer_fill = %zu;",
                        timeout, cb->send_buffer_fill);

        if (timeout > 0)
        {
                time_t now;

                now = time (NULL);
                if ((cb->send_buffer_init_time + timeout) > now)
                        return (0);
        }

        if (cb->format == WH_FORMAT_COMMAND)
        {
                if (cb->send_buffer_fill <= 0)
                {
                        cb->send_buffer_init_time = time (NULL);
                        return (0);
                }

                status = wh_send_buffer (cb);
                wh_reset_buffer (cb);
        }
        else if (cb->format == WH_FORMAT_JSON)
        {
                if (cb->send_buffer_fill <= 2)
                {
                        cb->send_buffer_init_time = time (NULL);
                        return (0);
                }

                status = format_json_finalize (cb->send_buffer,
                                &cb->send_buffer_fill,
                                &cb->send_buffer_free);
                if (status != 0)
                {
                        ERROR ("write_http: wh_flush_nolock: "
                                        "format_json_finalize failed.");
                        wh_reset_buffer (cb);
                        return (status);
                }

                status = wh_send_buffer (cb);
                wh_reset_buffer (cb);
        }
        else
        {
                ERROR ("write_http: wh_flush_nolock: "
                                "Unknown format: %i",
                                cb->format);
                return (-1);
        }

        return (status);
}