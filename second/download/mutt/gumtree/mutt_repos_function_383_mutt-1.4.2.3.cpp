int mutt_query_complete (char *buf, size_t buflen)
{
  QUERY *results = NULL;

  if (!QueryCmd)
  {
    mutt_error _("Query command not defined.");
    return 0;
  }

  results = run_query (buf, 1);
  if (results)
  {
    /* only one response? */
    if (results->next == NULL)
    {
      buf[0] = '\0';
      rfc822_write_address (buf, buflen, result_to_addr(results));
      mutt_clear_error ();
      return (0);
    }
    /* multiple results, choose from query menu */
    query_menu (buf, buflen, results, 1);
  }
  return (0);
}