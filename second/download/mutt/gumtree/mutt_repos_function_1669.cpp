static int parse_attach_list (BUFFER *buf, BUFFER *s, LIST **ldata, BUFFER *err)
{
  ATTACH_MATCH *a;
  LIST *listp, *lastp;
  char *p;
  char *tmpminor;
  int len;
  int ret;

  /* Find the last item in the list that data points to. */
  lastp = NULL;
  dprint(5, (debugfile, "parse_attach_list: ldata = %p, *ldata = %p\n",
	      (void *)ldata, (void *)*ldata));
  for (listp = *ldata; listp; listp = listp->next)
  {
    a = (ATTACH_MATCH *)listp->data;
    dprint(5, (debugfile, "parse_attach_list: skipping %s/%s\n",
		a->major, a->minor));
    lastp = listp;
  }

  do
  {
    mutt_extract_token (buf, s, 0);

    if (!buf->data || *buf->data == '\0')
      continue;
   
    a = safe_malloc(sizeof(ATTACH_MATCH));

    /* some cheap hacks that I expect to remove */
    if (!ascii_strcasecmp(buf->data, "any"))
      a->major = safe_strdup("*/.*");
    else if (!ascii_strcasecmp(buf->data, "none"))
      a->major = safe_strdup("cheap_hack/this_should_never_match");
    else
      a->major = safe_strdup(buf->data);

    if ((p = strchr(a->major, '/')))
    {
      *p = '\0';
      ++p;
      a->minor = p;
    }
    else
    {
      a->minor = "unknown";
    }

    len = strlen(a->minor);
    tmpminor = safe_malloc(len+3);
    strcpy(&tmpminor[1], a->minor); /* __STRCPY_CHECKED__ */
    tmpminor[0] = '^';
    tmpminor[len+1] = '$';
    tmpminor[len+2] = '\0';

    a->major_int = mutt_check_mime_type(a->major);
    ret = REGCOMP(&a->minor_rx, tmpminor, REG_ICASE);

    FREE(&tmpminor);

    if (ret)
    {
      regerror(ret, &a->minor_rx, err->data, err->dsize);
      FREE(&a->major);
      FREE(&a);
      return -1;
    }

    dprint(5, (debugfile, "parse_attach_list: added %s/%s [%d]\n",
		a->major, a->minor, a->major_int));

    listp = safe_malloc(sizeof(LIST));
    listp->data = (char *)a;
    listp->next = NULL;
    if (lastp)
    {
      lastp->next = listp;
    }
    else
    {
      *ldata = listp;
    }
    lastp = listp;
  }
  while (MoreArgs (s));
   
  _attachments_clean();
  return 0;
}