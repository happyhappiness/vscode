static int pop_fetch_headers (CONTEXT *ctx)
{
  int i, ret, old_count, new_count;
  POP_DATA *pop_data = (POP_DATA *)ctx->data;

  time (&pop_data->check_time);
  pop_data->clear_cache = 0;

  for (i = 0; i < ctx->msgcount; i++)
    ctx->hdrs[i]->refno = -1;

  old_count = ctx->msgcount;
  ret = pop_fetch_data (pop_data, "UIDL\r\n", NULL, fetch_uidl, ctx);
  new_count = ctx->msgcount;
  ctx->msgcount = old_count;

  if (pop_data->cmd_uidl == 2)
  {
    if (ret == 0)
    {
      pop_data->cmd_uidl = 1;

      dprint (1, (debugfile, "pop_fetch_headers: set UIDL capability\n"));
    }

    if (ret == -2 && pop_data->cmd_uidl == 2)
    {
      pop_data->cmd_uidl = 0;

      dprint (1, (debugfile, "pop_fetch_headers: unset UIDL capability\n"));
      snprintf (pop_data->err_msg, sizeof (pop_data->err_msg),
	      _("Command UIDL is not supported by server."));
    }
  }

  if (ret == 0)
  {
    for (i = 0; i < old_count; i++)
      if (ctx->hdrs[i]->refno == -1)
	ctx->hdrs[i]->deleted = 1;

    for (i = old_count; i < new_count; i++)
    {
      mutt_message (_("Fetching message headers... [%d/%d]"),
		    i + 1 - old_count, new_count - old_count);

      ret = pop_read_header (pop_data, ctx->hdrs[i]);
      if (ret < 0)
	break;

      ctx->msgcount++;
    }

    if (i > old_count)
      mx_update_context (ctx, i - old_count);
  }

  if (ret < 0)
  {
    for (i = ctx->msgcount; i < new_count; i++)
      mutt_free_header (&ctx->hdrs[i]);
    return ret;
  }

  mutt_clear_error ();
  return (new_count - old_count);
}