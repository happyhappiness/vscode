static char *intl_to_local (char *orig_user, char *orig_domain, int flags)
{
  char *local_user = NULL, *local_domain = NULL, *mailbox = NULL;
  char *reversed_user = NULL, *reversed_domain = NULL;
  char *tmp = NULL;
#ifdef HAVE_LIBIDN
  int is_idn_encoded = 0;
#endif /* HAVE_LIBIDN */

  local_user = safe_strdup (orig_user);
  local_domain = safe_strdup (orig_domain);

#ifdef HAVE_LIBIDN
  is_idn_encoded = check_idn (local_domain);
  if (is_idn_encoded && option (OPTIDNDECODE))
  {
    if (idna_to_unicode_8z8z (local_domain, &tmp, IDNA_ALLOW_UNASSIGNED) != IDNA_SUCCESS)
      goto cleanup;
    mutt_str_replace (&local_domain, tmp);
    FREE (&tmp);
  }
#endif /* HAVE_LIBIDN */

  /* we don't want charset-hook effects, so we set flags to 0 */
  if (mutt_convert_string (&local_user, "utf-8", Charset, 0) == -1)
    goto cleanup;

  if (mutt_convert_string (&local_domain, "utf-8", Charset, 0) == -1)
    goto cleanup;

  /*
   * make sure that we can convert back and come out with the same
   * user and domain name.
   */
  if ((flags & MI_MAY_BE_IRREVERSIBLE) == 0)
  {
    reversed_user = safe_strdup (local_user);

    if (mutt_convert_string (&reversed_user, Charset, "utf-8", 0) == -1)
    {
      dprint (1, (debugfile,
                  "intl_to_local: Not reversible. Charset conv to utf-8 failed for user = '%s'.\n",
                  reversed_user));
      goto cleanup;
    }

    if (ascii_strcasecmp (orig_user, reversed_user))
    {
      dprint (1, (debugfile, "intl_to_local: Not reversible. orig = '%s', reversed = '%s'.\n",
                  orig_user, reversed_user));
      goto cleanup;
    }

    reversed_domain = safe_strdup (local_domain);

    if (mutt_convert_string (&reversed_domain, Charset, "utf-8", 0) == -1)
    {
      dprint (1, (debugfile,
                  "intl_to_local: Not reversible. Charset conv to utf-8 failed for domain = '%s'.\n",
                  reversed_domain));
      goto cleanup;
    }

#ifdef HAVE_LIBIDN
    /* If the original domain was UTF-8, idna encoding here could
     * produce a non-matching domain!  Thus we only want to do the
     * idna_to_ascii_8z() if the original domain was IDNA encoded.
     */
    if (is_idn_encoded && option (OPTIDNDECODE))
    {
      if (idna_to_ascii_8z (reversed_domain, &tmp, IDNA_ALLOW_UNASSIGNED) != IDNA_SUCCESS)
      {
        dprint (1, (debugfile,
                    "intl_to_local: Not reversible. idna_to_ascii_8z failed for domain = '%s'.\n",
                    reversed_domain));
        goto cleanup;
      }
      mutt_str_replace (&reversed_domain, tmp);
    }
#endif /* HAVE_LIBIDN */

    if (ascii_strcasecmp (orig_domain, reversed_domain))
    {
      dprint (1, (debugfile, "intl_to_local: Not reversible. orig = '%s', reversed = '%s'.\n",
                  orig_domain, reversed_domain));
      goto cleanup;
    }
  }

  mailbox = safe_malloc (mutt_strlen (local_user) + mutt_strlen (local_domain) + 2);
  sprintf (mailbox, "%s@%s", NONULL(local_user), NONULL(local_domain)); /* __SPRINTF_CHECKED__ */

cleanup:
  FREE (&local_user);
  FREE (&local_domain);
  FREE (&tmp);
  FREE (&reversed_domain);
  FREE (&reversed_user);

  return mailbox;
}