void mutt_query_menu (char *buf, size_t buflen)
{
  if (!QueryCmd)
  {
    mutt_error _("Query command not defined.");
    return;
  }

  if (buf == NULL)
  {
    char buffer[STRING] = "";

    query_menu (buffer, sizeof (buffer), NULL, 0);
  }
  else
  {
    query_menu (buf, buflen, NULL, 1);
  }
}