int pgp_check_traditional (FILE *fp, BODY *b, int tagged_only)
{
  int rv = 0;
  int r;
  for (; b; b = b->next)
  {
    if (is_multipart (b))
      rv = pgp_check_traditional (fp, b->parts, tagged_only) || rv;
    else if (b->type == TYPETEXT)
    {
      if ((r = mutt_is_application_pgp (b)))
	rv = rv || r;
      else
	rv = pgp_check_traditional_one_body (fp, b, tagged_only) || rv;
    }
  }

  return rv;
}