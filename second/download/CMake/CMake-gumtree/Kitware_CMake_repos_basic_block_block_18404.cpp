(ctx->busy_polling != 0)
    if (ctx->busy_polling < 0 || !statbuf_eq(&ctx->statbuf, statbuf))
      ctx->poll_cb(ctx->parent_handle, 0, &ctx->statbuf, statbuf)