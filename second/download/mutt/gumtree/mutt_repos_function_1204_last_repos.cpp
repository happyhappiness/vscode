static char *local_to_intl (char *user, char *domain)
{
  char *intl_user = NULL, *intl_domain = NULL;
  char *mailbox = NULL;
  char *tmp = NULL;

  intl_user = safe_strdup (user);
  intl_domain = safe_strdup (domain);

  /* we don't want charset-hook effects, so we set flags to 0 */
  if (mutt_convert_string (&intl_user, Charset, "utf-8", 0) == -1)
    goto cleanup;

  if (mutt_convert_string (&intl_domain, Charset, "utf-8", 0) == -1)
    goto cleanup;

#ifdef HAVE_LIBIDN
  if (option (OPTIDNENCODE))
  {
    if (idna_to_ascii_8z (intl_domain, &tmp, IDNA_ALLOW_UNASSIGNED) != IDNA_SUCCESS)
      goto cleanup;
    mutt_str_replace (&intl_domain, tmp);
  }
#endif /* HAVE_LIBIDN */

  mailbox = safe_malloc (mutt_strlen (intl_user) + mutt_strlen (intl_domain) + 2);
  sprintf (mailbox, "%s@%s", NONULL(intl_user), NONULL(intl_domain)); /* __SPRINTF_CHECKED__ */

cleanup:
  FREE (&intl_user);
  FREE (&intl_domain);
  FREE (&tmp);

  return mailbox;
}