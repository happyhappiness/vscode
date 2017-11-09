static int check_host (X509 *x509cert, const char *hostname, char *err, size_t errlen)
{
  int i, rc = 0;
  /* hostname in ASCII format: */
  char *hostname_ascii = NULL;
  /* needed to get the common name: */
  X509_NAME *x509_subject;
  char *buf = NULL;
  int bufsize;
  /* needed to get the DNS subjectAltNames: */
  STACK_OF(GENERAL_NAME) *subj_alt_names;
  int subj_alt_names_count;
  GENERAL_NAME *subj_alt_name;
  /* did we find a name matching hostname? */
  int match_found;

  /* Check if 'hostname' matches the one of the subjectAltName extensions of
   * type DNS or the Common Name (CN). */

#ifdef HAVE_LIBIDN
  if (idna_to_ascii_lz(hostname, &hostname_ascii, 0) != IDNA_SUCCESS)
  {
    hostname_ascii = safe_strdup(hostname);
  }
#else
  hostname_ascii = safe_strdup(hostname);
#endif

  /* Try the DNS subjectAltNames. */
  match_found = 0;
  if ((subj_alt_names = X509_get_ext_d2i(x509cert, NID_subject_alt_name,
					 NULL, NULL)))
  {
    subj_alt_names_count = sk_GENERAL_NAME_num(subj_alt_names);
    for (i = 0; i < subj_alt_names_count; i++)
    {
      subj_alt_name = sk_GENERAL_NAME_value(subj_alt_names, i);
      if (subj_alt_name->type == GEN_DNS)
      {
	if (subj_alt_name->d.ia5->length >= 0 &&
	    mutt_strlen((char *)subj_alt_name->d.ia5->data) == (size_t)subj_alt_name->d.ia5->length &&
	    (match_found = hostname_match(hostname_ascii,
					  (char *)(subj_alt_name->d.ia5->data))))
	{
	  break;
	}
      }
    }
    GENERAL_NAMES_free(subj_alt_names);
  }

  if (!match_found)
  {
    /* Try the common name */
    if (!(x509_subject = X509_get_subject_name(x509cert)))
    {
      if (err && errlen)
	strfcpy (err, _("cannot get certificate subject"), errlen);
      goto out;
    }

    /* first get the space requirements */
    bufsize = X509_NAME_get_text_by_NID(x509_subject, NID_commonName,
					NULL, 0);
    if (bufsize == -1)
    {
      if (err && errlen)
	strfcpy (err, _("cannot get certificate common name"), errlen);
      goto out;
    }
    bufsize++; /* space for the terminal nul char */
    buf = safe_malloc((size_t)bufsize);
    if (X509_NAME_get_text_by_NID(x509_subject, NID_commonName,
				  buf, bufsize) == -1)
    {
      if (err && errlen)
	strfcpy (err, _("cannot get certificate common name"), errlen);
      goto out;
    }
    /* cast is safe since bufsize is incremented above, so bufsize-1 is always
     * zero or greater.
     */
    if (mutt_strlen(buf) == (size_t)bufsize - 1) {
      match_found = hostname_match(hostname_ascii, buf);
    }
  }

  if (!match_found)
  {
    if (err && errlen)
      snprintf (err, errlen, _("certificate owner does not match hostname %s"),
		hostname);
    goto out;
  }

  rc = 1;

out:
  FREE(&buf);
  FREE(&hostname_ascii);

  return rc;
}