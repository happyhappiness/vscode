int
mutt_copy_hdr (FILE *in, FILE *out, LOFF_T off_start, LOFF_T off_end, int flags,
	       const char *prefix)
{
  int from = 0;
  int this_is_from;
  int ignore = 0;
  char buf[LONG_STRING]; /* should be long enough to get most fields in one pass */
  char *nl;
  LIST *t;
  char **headers;
  int hdr_count;
  int x;
  char *this_one = NULL;
  size_t this_one_len = 0;
  int error;

  if (ftello (in) != off_start)
    fseeko (in, off_start, 0);

  buf[0] = '\n';
  buf[1] = 0;

  if ((flags & (CH_REORDER | CH_WEED | CH_MIME | CH_DECODE | CH_PREFIX | CH_WEED_DELIVERED)) == 0)
  {
    /* Without these flags to complicate things
     * we can do a more efficient line to line copying
     */
    while (ftello (in) < off_end)
    {
      nl = strchr (buf, '\n');

      if ((fgets (buf, sizeof (buf), in)) == NULL)
	break;

      /* Is it the beginning of a header? */
      if (nl && buf[0] != ' ' && buf[0] != '\t')
      {
	ignore = 1;
	if (!from && mutt_strncmp ("From ", buf, 5) == 0)
	{
	  if ((flags & CH_FROM) == 0)
	    continue;
	  from = 1;
	}
	else if (flags & (CH_NOQFROM) &&
			ascii_strncasecmp (">From ", buf, 6) == 0)
		continue;

	else if (buf[0] == '\n' || (buf[0] == '\r' && buf[1] == '\n'))
	  break; /* end of header */

	if ((flags & (CH_UPDATE | CH_XMIT | CH_NOSTATUS)) &&
	    (ascii_strncasecmp ("Status:", buf, 7) == 0 ||
	     ascii_strncasecmp ("X-Status:", buf, 9) == 0))
	  continue;
	if ((flags & (CH_UPDATE_LEN | CH_XMIT | CH_NOLEN)) &&
	    (ascii_strncasecmp ("Content-Length:", buf, 15) == 0 ||
	     ascii_strncasecmp ("Lines:", buf, 6) == 0))
	  continue;
	if ((flags & CH_UPDATE_REFS) &&
	    ascii_strncasecmp ("References:", buf, 11) == 0)
	  continue;
	if ((flags & CH_UPDATE_IRT) &&
	    ascii_strncasecmp ("In-Reply-To:", buf, 12) == 0)
	  continue;
	ignore = 0;
      }

      if (!ignore && fputs (buf, out) == EOF)
	return (-1);
    }
    return 0;
  }

  hdr_count = 1;
  x = 0;
  error = FALSE;

  /* We are going to read and collect the headers in an array
   * so we are able to do re-ordering.
   * First count the number of entries in the array
   */
  if (flags & CH_REORDER)
  {
    for (t = HeaderOrderList; t; t = t->next)
    {
      dprint(3, (debugfile, "Reorder list: %s\n", t->data));
      hdr_count++;
    }
  }

  dprint (1, (debugfile, "WEED is %s\n", (flags & CH_WEED) ? "Set" : "Not"));

  headers = safe_calloc (hdr_count, sizeof (char *));

  /* Read all the headers into the array */
  while (ftello (in) < off_end)
  {
    nl = strchr (buf, '\n');

    /* Read a line */
    if ((fgets (buf, sizeof (buf), in)) == NULL)
      break;

    /* Is it the beginning of a header? */
    if (nl && buf[0] != ' ' && buf[0] != '\t')
    {
      /* Do we have anything pending? */
      if (this_one)
      {
	if (flags & CH_DECODE) 
	{
	  if (!address_header_decode (&this_one))
	    rfc2047_decode (&this_one);
	  this_one_len = mutt_strlen (this_one);
	}

	if (!headers[x])
	  headers[x] = this_one;
	else 
	{
	  int hlen = mutt_strlen (headers[x]);

	  safe_realloc (&headers[x], hlen + this_one_len + sizeof (char));
	  strcat (headers[x] + hlen, this_one); /* __STRCAT_CHECKED__ */
	  FREE (&this_one);
	}

	this_one = NULL;
      }

      ignore = 1;
      this_is_from = 0;
      if (!from && mutt_strncmp ("From ", buf, 5) == 0)
      {
	if ((flags & CH_FROM) == 0)
	  continue;
	this_is_from = from = 1;
      }
      else if (buf[0] == '\n' || (buf[0] == '\r' && buf[1] == '\n'))
	break; /* end of header */

      /* note: CH_FROM takes precedence over header weeding. */
      if (!((flags & CH_FROM) && (flags & CH_FORCE_FROM) && this_is_from) &&
	  (flags & CH_WEED) &&
	  mutt_matches_ignore (buf, Ignore) &&
	  !mutt_matches_ignore (buf, UnIgnore))
	continue;
      if ((flags & CH_WEED_DELIVERED) &&
	  ascii_strncasecmp ("Delivered-To:", buf, 13) == 0)
	continue;
      if ((flags & (CH_UPDATE | CH_XMIT | CH_NOSTATUS)) &&
	  (ascii_strncasecmp ("Status:", buf, 7) == 0 ||
	   ascii_strncasecmp ("X-Status:", buf, 9) == 0))
	continue;
      if ((flags & (CH_UPDATE_LEN | CH_XMIT | CH_NOLEN)) &&
	  (ascii_strnca