{
  struct poll_ctx* ctx;
  uv_loop_t* loop;
  size_t len;
  int err;

  if (uv__is_active(handle))
    return 0;

  loop = handle->loop;
  len = strlen(path);
  ctx = uv__calloc(1, sizeof(*ctx) + len);

  if (ctx == NULL)
    return UV_ENOMEM;

  ctx->loop = loop;
  ctx->poll_cb = cb;
  ctx->interval = interval ? interval : 1;
  ctx->start_time = uv_now(loop);
  ctx->parent_handle = handle;
  memcpy(ctx->path, path, len + 1);

  err = uv_timer_init(loop, &ctx->timer_handle);
  if (err < 0)
    goto error;

  ctx->timer_handle.flags |= UV__HANDLE_INTERNAL;
  uv__handle_unref(&ctx->timer_handle);

  err = uv_fs_stat(loop, &ctx->fs_req, ctx->path, poll_cb);
  if (err < 0)
    goto error;

  handle->poll_ctx = ctx;
  uv__handle_start(handle);

  return 0;

error:
  uv__free(ctx);
  return err;
}