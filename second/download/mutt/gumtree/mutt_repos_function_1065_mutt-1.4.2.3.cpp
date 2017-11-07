int pop_open_connection (POP_DATA *pop_data)
{
  int ret;
  unsigned int n, size;
  char buf[LONG_STRING];

  ret = pop_connect (pop_data);
  if (ret < 0)
  {
    mutt_sleep (2);
    return ret;
  }

  ret = pop_capabilities (pop_data);
  if (ret == -1)
    goto err_conn;
  if (ret == -2)
  {
    mutt_sleep (2);
    return -2;
  }

  ret = pop_authenticate (pop_data);
  if (ret == -1)
    goto err_conn;
  if (ret == -3)
    mutt_clear_error ();
  if (ret != 0)
    return ret;

  /* get total size of mailbox */
  strfcpy (buf, "STAT\r\n", sizeof (buf));
  ret = pop_query (pop_data, buf, sizeof (buf));
  if (ret == -1)
    goto err_conn;
  if (ret == -2)
  {
    mutt_error ("%s", pop_data->err_msg);
    mutt_sleep (2);
    return ret;
  }

  sscanf (buf, "+OK %u %u", &n, &size);
  pop_data->size = size;
  return 0;

err_conn:
  pop_data->status = POP_DISCONNECTED;
  mutt_error _("Server closed connection!");
  mutt_sleep (2);
  return -1;
}