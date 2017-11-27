static void wh_reset_buffer (wh_callback_t *cb)  /* {{{ */
{
        memset (cb->send_buffer, 0, cb->send_buffer_size);
        cb->send_buffer_free = cb->send_buffer_size;
        cb->send_buffer_fill = 0;
        cb->send_buffer_init_time = cdtime ();

        if (cb->format == WH_FORMAT_JSON)
        {
                format_json_initialize (cb->send_buffer,
                                &cb->send_buffer_fill,
                                &cb->send_buffer_free);
        }
}