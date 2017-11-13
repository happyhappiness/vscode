int
mutt_copy_header (FILE *in, HEADER *h, FILE *out, int flags, const char *prefix)
{
  char buffer[SHORT_STRING];

  if (h->env)
    flags |= (h->env->irt_changed ? CH_UPDATE_IRT : 0)
      | (h->env->refs_changed ? CH_UPDATE_REFS : 0);
  
  if (mutt_copy_hdr (in, out, h->offset, h->content->offset, flags, prefix) == -1)
    return -1;

  if (flags & CH_TXTPLAIN)
  {
    char chsbuf[SHORT_STRING];
    fputs ("MIME-Version: 1.0\n", out);
    fputs ("Content-Transfer-Encoding: 8bit\n", out);
    fputs ("Content-Type: text/plain; charset=", out);
    mutt_canonical_charset (chsbuf, sizeof (chsbuf), Charset ? Charset : "us-ascii");
    rfc822_cat(buffer, sizeof(buffer), chsbuf, MimeSpecials);
    fputs(buffer, out);
    fputc('\n', out);
  }

  if ((flags & CH_UPDATE_IRT) && h->env->in_reply_to)
  {
    LIST *listp = h->env->in_reply_to;
    fputs ("In-Reply-To:", out);
    for (; listp; listp = listp->next)
    {
      fputc (' ', out);
      fputs (listp->data, out);
    }
    fputc ('\n', out);
  }

  if ((flags & CH_UPDATE_REFS) && h->env->references)
  {
    fputs ("References:", out);
    mutt_write_references (h->env->references, out, 0);
    fputc ('\n', out);
  }

  if ((flags & CH_UPDATE) && (flags & CH_NOSTATUS) == 0)
  {
    if (h->old || h->read)
    {
      fputs ("Status: ", out);
      if (h->read)
	fputs ("RO", out);
      else if (h->old)
	fputc ('O', out);
      fputc ('\n', out);
    }

    if (h->flagged || h->replied)
    {
      fputs ("X-Status: ", out);
      if (h->replied)
	fputc ('A', out);
      if (h->flagged)
	fputc ('F', out);
      fputc ('\n', out);
    }
  }

  if (flags & CH_UPDATE_LEN &&
      (flags & CH_NOLEN) == 0)
  {
    fprintf (out, "Content-Length: " OFF_T_FMT "\n", h->content->length);
    if (h->lines != 0 || h->content->length == 0)
      fprintf (out, "Lines: %d\n", h->lines);
  }

  if (flags & CH_UPDATE_LABEL)
  {
    h->xlabel_changed = 0;
    if (h->env->x_label != NULL)
      if (fprintf(out, "X-Label: %s\n", h->env->x_label) !=
		  10 + strlen(h->env->x_label))
        return -1;
  }

  if ((flags & CH_NONEWLINE) == 0)
  {
    if (flags & CH_PREFIX)
      fputs(prefix, out);
    fputc ('\n', out); /* add header terminator */
  }

  if (ferror (out) || feof (out))
    return -1;
  
  return 0;
}