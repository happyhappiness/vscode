int pop_sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  int i, ret;
  char buf[LONG_STRING];
  POP_DATA *pop_data = (POP_DATA *)ctx->data;

  pop_data->check_time = 0;

  FOREVER
  {
    if (pop_reconnect (ctx) < 0)
      return -1;

    mutt_message (_("Marking %d messages deleted..."), ctx->deleted);

    for (i = 0, ret = 0; ret == 0 && i < ctx->msgcount; i++)
    {
      if (ctx->hdrs[i]->deleted)
      {
	snprintf (buf, sizeof (buf), "DELE %d\r\n", ctx->hdrs[i]->refno);
	ret = pop_query (pop_data, buf, sizeof (buf));
      }
    }

    if (ret == 0)
    {
      strfcpy (buf, "QUIT\r\n", sizeof (buf));
      ret = pop_query (pop_data, buf, sizeof (buf));
    }

    if (ret == 0)
    {
      pop_data->clear_cache = 1;
      pop_clear_cache (pop_data);
      pop_data->status = POP_DISCONNECTED;
      return 0;
    }

    if (ret == -2)
    {
      mutt_error ("%s", pop_data->err_msg);
      mutt_sleep (2);
      return -1;
    }
  }
}