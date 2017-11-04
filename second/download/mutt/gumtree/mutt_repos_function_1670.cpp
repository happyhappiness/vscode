static int parse_unattach_list (BUFFER *buf, BUFFER *s, LIST **ldata, BUFFER *err)
{
  ATTACH_MATCH *a;
  LIST *lp, *lastp, *newlp;
  char *tmp;
  int major;
  char *minor;

  do
  {
    mutt_extract_token (buf, s, 0);

    if (!ascii_strcasecmp(buf->data, "any"))
      tmp = safe_strdup("*/.*");
    else if (!ascii_strcasecmp(buf->data, "none"))
      tmp = safe_strdup("cheap_hack/this_should_never_match");
    else
      tmp = safe_strdup(buf->data);

    if ((minor = strchr(tmp, '/')))
    {
      *minor = '\0';
      ++minor;
    }
    else
    {
      minor = "unknown";
    }
    major = mutt_check_mime_type(tmp);

    /* We must do our own walk here because remove_from_list() will only
     * remove the LIST->data, not anything pointed to by the LIST->data. */
    lastp = NULL;
    for(lp = *ldata; lp; )
    {
      a = (ATTACH_MATCH *)lp->data;
      dprint(5, (debugfile, "parse_unattach_list: check %s/%s [%d] : %s/%s [%d]\n",
		  a->major, a->minor, a->major_int, tmp, minor, major));
      if (a->major_int == major && !mutt_strcasecmp(minor, a->minor))
      {
	dprint(5, (debugfile, "parse_unattach_list: removed %s/%s [%d]\n",
		    a->major, a->minor, a->major_int));
	regfree(&a->minor_rx);
	FREE(&a->major);

	/* Relink backward */
	if (lastp)
	  lastp->next = lp->next;
	else
	  *ldata = lp->next;

        newlp = lp->next;
        FREE(&lp->data);	/* same as a */
        FREE(&lp);
        lp = newlp;
        continue;
      }

      lastp = lp;
      lp = lp->next;
    }

  }
  while (MoreArgs (s));
   
  FREE(&tmp);
  _attachments_clean();
  return 0;
}