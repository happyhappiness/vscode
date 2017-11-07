void pop_logout (CONTEXT *ctx)
{
  int ret = 0;
  char buf[LONG_STRING];
  POP_DATA *pop_data = (POP_DATA *)ctx->data;

  if (pop_data->status == POP_CONNECTED)
  {
    mutt_message _("Closing connection to POP server...");

    if (ctx->readonly)
    {
      strfcpy (buf, "RSET\r\n", sizeof (buf));
      ret = pop_query (pop_data, buf, sizeof (buf));
    }

    if (ret != -1)
    {
      strfcpy (buf, "QUIT\r\n", sizeof (buf));
      pop_query (pop_data, buf, sizeof (buf));
    }

    mutt_clear_error ();
  }

  pop_data->status = POP_DISCONNECTED;
  return;
}