int mutt_query_complete (char *buf, size_t buflen)
{
  QUERY *results = NULL;
  ADDRESS *tmpa;

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
      tmpa = result_to_addr (results);
      mutt_addrlist_to_local (tmpa);
      buf[0] = '\0';
      rfc822_write_address (buf, buflen, tmpa, 0);
      rfc822_free_address (&tmpa);
      free_query (&results);
      mutt_clear_error ();
      return (0);
    }
    /* multiple results, choose from query menu */
    query_menu (buf, buflen, results, 1);
  }
  return (0);
}