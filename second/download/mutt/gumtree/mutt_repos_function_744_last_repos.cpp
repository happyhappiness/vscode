int pgp_gpgme_check_traditional (FILE *fp, BODY *b, int just_one)
{
  int rv = 0;
  int r;
  for (; b; b = b->next)
  {
    if (!just_one && is_multipart (b))
      rv = (pgp_gpgme_check_traditional (fp, b->parts, 0) || rv);
    else if (b->type == TYPETEXT)
    {
      if ((r = mutt_is_application_pgp (b)))
	rv = (rv || r);
      else
	rv = (pgp_check_traditional_one_body (fp, b) || rv);
    }

    if (just_one)
      break;
  }
  return rv;
}