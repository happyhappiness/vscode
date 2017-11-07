void pop_close_mailbox (CONTEXT *ctx)
{
  POP_DATA *pop_data = (POP_DATA *)ctx->data;

  if (!pop_data)
    return;

  pop_logout (ctx);

  if (pop_data->status != POP_NONE)
    mutt_socket_close (pop_data->conn);

  pop_data->status = POP_NONE;

  pop_data->clear_cache = 1;
  pop_clear_cache (pop_data);

  if (!pop_data->conn->data)
    mutt_socket_free (pop_data->conn);

  return;
}