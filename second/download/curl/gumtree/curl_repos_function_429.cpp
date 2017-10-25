static void fix_hostname(struct connectdata *conn, struct hostname *host)
{
  /* set the name we use to display the host name */
  host->dispname = host->name;

#ifdef USE_LIBIDN
  /*************************************************************
   * Check name for non-ASCII and convert hostname to ACE form.
   *************************************************************/
  if (!is_ASCII_name(host->name) &&
      stringprep_check_version(LIBIDN_REQUIRED_VERSION)) {
    char *ace_hostname = NULL;
    struct SessionHandle *data = conn->data;
    int rc = idna_to_ascii_lz(host->name, &ace_hostname, 0);
    infof (data, "Input domain encoded as `%s'\n",
           stringprep_locale_charset ());
    if (rc != IDNA_SUCCESS)
      infof(data, "Failed to convert %s to ACE; %s\n",
            host->name, Curl_idn_strerror(conn,rc));
    else {
      tld_check_name(data, ace_hostname);

      host->encalloc = ace_hostname;
      /* change the name pointer to point to the encoded hostname */
      host->name = host->encalloc;
    }
  }
#else
  (void)conn; /* never used */
#endif
}