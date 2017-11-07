int pop_reconnect (CONTEXT *ctx)
{
  int ret;
  POP_DATA *pop_data = (POP_DATA *)ctx->data;

  if (pop_data->status == POP_CONNECTED)
    return 0;
  if (pop_data->status == POP_BYE)
    return -1;

  FOREVER
  {
    mutt_socket_close (pop_data->conn);

    ret = pop_open_connection (pop_data);
    if (ret == 0)
    {
      char *msg = _("Verifying message indexes...");
      int i;

      for (i = 0; i < ctx->msgcount; i++)
	ctx->hdrs[i]->refno = -1;

      mutt_message (msg);

      ret = pop_fetch_data (pop_data, "UIDL\r\n", msg, check_uidl, ctx);
      if (ret == -2)
      {
        mutt_error ("%s", pop_data->err_msg);
        mutt_sleep (2);
      }
    }
    if (ret == 0)
      return 0;

    pop_logout (ctx);

    if (ret < -1)
      return -1;

    if (query_quadoption (OPT_POPRECONNECT,
		_("Connection lost. Reconnect to POP server?")) != M_YES)
      return -1;
  }
}