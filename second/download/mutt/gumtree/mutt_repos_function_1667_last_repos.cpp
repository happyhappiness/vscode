void pop_error (POP_DATA *pop_data, char *msg)
{
  char *t, *c, *c2;

  t = strchr (pop_data->err_msg, '\0');
  c = msg;

  if (!mutt_strncmp (msg, "-ERR ", 5))
  {
    c2 = skip_email_wsp(msg + 5);

    if (*c2)
      c = c2;
  }

  strfcpy (t, c, sizeof (pop_data->err_msg) - strlen (pop_data->err_msg));
  mutt_remove_trailing_ws (pop_data->err_msg);
}