{
      ctx->poll_cb(ctx->parent_handle,
                   req->result,
                   &ctx->statbuf,
                   &zero_statbuf);
      ctx->busy_polling = req->result;
    }