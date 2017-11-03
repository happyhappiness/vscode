void pop_apop_timestamp (POP_DATA *pop_data, char *buf)
{
  char *p1, *p2;

  FREE (&pop_data->timestamp);

  if ((p1 = strchr (buf, '<')) && (p2 = strchr (p1, '>')))
  {
    p2[1] = '\0';
    pop_data->timestamp = safe_strdup (p1);
  }
}