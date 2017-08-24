{
  uv_stat_t* statbuf;
  struct poll_ctx* ctx;
  uint64_t interval;

  ctx = container_of(req, struct poll_ctx, fs_req);

  if (ctx->parent_handle == NULL) { /* handle has been stopped or closed */
    uv_close((uv_handle_t*)&ctx->timer_handle, timer_close_cb);
    uv_fs_req_cleanup(req);
    return;
  }

  if (req->result != 0) {
    if (ctx->busy_polling != req->result) {
      ctx->poll_cb(ctx->parent_handle,
                   req->result,
                   &ctx->statbuf,
                   &zero_statbuf);
      ctx->busy_polling = req->result;
    }
    goto out;
  }

  statbuf = &req->statbuf;

  if (ctx->busy_polling != 0)
    if (ctx->busy_polling < 0 || !statbuf_eq(&ctx->statbuf, statbuf))
      ctx->poll_cb(ctx->parent_handle, 0, &ctx->statbuf, statbuf);

  ctx->statbuf = *statbuf;
  ctx->busy_polling = 1;

out:
  uv_fs_req_cleanup(req);

  if (ctx->parent_handle == NULL) { /* handle has been stopped by callback */
    uv_close((uv_handle_t*)&ctx->timer_handle, timer_close_cb);
    return;
  }

  /* Reschedule timer, subtract the delay from doing the stat(). */
  interval = ctx->interval;
  interval -= (uv_now(ctx->loop) - ctx->start_time) % interval;

  if (uv_timer_start(&ctx->timer_handle, timer_cb, interval, 0))
    abort();
}