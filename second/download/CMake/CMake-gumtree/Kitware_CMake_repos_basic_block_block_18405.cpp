{ /* handle has been stopped or closed */
    uv_close((uv_handle_t*)&ctx->timer_handle, timer_close_cb);
    uv_fs_req_cleanup(req);
    return;
  }