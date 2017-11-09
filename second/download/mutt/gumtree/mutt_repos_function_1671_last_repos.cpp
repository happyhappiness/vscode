int pop_connect (POP_DATA *pop_data)
{
  char buf[LONG_STRING];

  pop_data->status = POP_NONE;
  if (mutt_socket_open (pop_data->conn) < 0 ||
      mutt_socket_readln (buf, sizeof (buf), pop_data->conn) < 0)
  {
    mutt_error (_("Error connecting to server: %s"), pop_data->conn->account.host);
    return -1;
  }

  pop_data->status = POP_CONNECTED;

  if (mutt_strncmp (buf, "+OK", 3))
  {
    *pop_data->err_msg = '\0';
    pop_error (pop_data, buf);
    mutt_error ("%s", pop_data->err_msg);
    return -2;
  }

  pop_apop_timestamp (pop_data, buf);

  return 0;
}