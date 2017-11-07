static int pop_check_mailbox (CONTEXT *ctx, int *index_hint)
{
  int ret;
  POP_DATA *pop_data = (POP_DATA *)ctx->data;

  if ((pop_data->check_time + PopCheckTimeout) > time (NULL))
    return 0;

  pop_logout (ctx);

  mutt_socket_close (pop_data->conn);

  if (pop_open_connection (pop_data) < 0)
    return -1;

  ctx->size = pop_data->size;

  mutt_message _("Checking for new messages...");

  ret = pop_fetch_headers (ctx);
  pop_clear_cache (pop_data);

  if (ret < 0)
    return -1;

  if (ret > 0)
    return MUTT_NEW_MAIL;

  return 0;
}