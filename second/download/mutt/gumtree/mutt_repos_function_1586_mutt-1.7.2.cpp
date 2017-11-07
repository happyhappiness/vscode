int pop_query_d (POP_DATA *pop_data, char *buf, size_t buflen, char *msg)
{
  int dbg = MUTT_SOCK_LOG_CMD;
  char *c;

  if (pop_data->status != POP_CONNECTED)
    return -1;

#ifdef DEBUG
    /* print msg instead of real command */
    if (msg)
    {
      dbg = MUTT_SOCK_LOG_FULL;
      dprint (MUTT_SOCK_LOG_CMD, (debugfile, "> %s", msg));
    }
#endif

  mutt_socket_write_d (pop_data->conn, buf, -1, dbg);

  c = strpbrk (buf, " \r\n");
  *c = '\0';
  snprintf (pop_data->err_msg, sizeof (pop_data->err_msg), "%s: ", buf);

  if (mutt_socket_readln (buf, buflen, pop_data->conn) < 0)
  {
    pop_data->status = POP_DISCONNECTED;
    return -1;
  }
  if (!mutt_strncmp (buf, "+OK", 3))
    return 0;

  pop_error (pop_data, buf);
  return -2;
}