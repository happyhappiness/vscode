void imap_free_header_data (void** data)
{
  /* this should be safe even if the list wasn't used */
  mutt_free_list (&(((IMAP_HEADER_DATA*) *data)->keywords));

  safe_free (data);
}