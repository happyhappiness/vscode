(uv__is_active(&ctx->timer_handle))
    uv_close((uv_handle_t*)&ctx->timer_handle, timer_close_cb)