static void wt_reset_buffer(struct wt_callback *cb)
{
    memset(cb->send_buf, 0, sizeof(cb->send_buf));
    cb->send_buf_free = sizeof(cb->send_buf);
    cb->send_buf_fill = 0;
    cb->send_buf_init_time = cdtime();
}