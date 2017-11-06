void rfc3676_space_stuff (HEADER* hdr)
{
#if DEBUG
  int lc = 0;
  size_t len = 0;
  unsigned char c = '\0';
#endif
  FILE *in = NULL, *out = NULL;
  char buf[LONG_STRING];
  char tmpfile[_POSIX_PATH_MAX];

  if (!hdr || !hdr->content || !hdr->content->filename)
    return;

  dprint (2, (debugfile, "f=f: postprocess %s\n", hdr->content->filename));

  if ((in = safe_fopen (hdr->content->filename, "r")) == NULL)
    return;

  mutt_mktemp (tmpfile, sizeof (tmpfile));
  if ((out = safe_fopen (tmpfile, "w+")) == NULL)
  {
    safe_fclose (&in);
    return;
  }

  while (fgets (buf, sizeof (buf), in))
  {
    if (ascii_strncmp ("From ", buf, 5) == 0 || buf[0] == ' ') {
      fputc (' ', out);
#if DEBUG
      lc++;
      len = mutt_strlen (buf);
      if (len > 0)
      {
        c = buf[len-1];
        buf[len-1] = '\0';
      }
      dprint (4, (debugfile, "f=f: line %d needs space-stuffing: '%s'\n",
                  lc, buf));
      if (len > 0)
        buf[len-1] = c;
#endif
    }
    fputs (buf, out);
  }
  safe_fclose (&in);
  safe_fclose (&out);
  mutt_set_mtime (hdr->content->filename, tmpfile);
  unlink (hdr->content->filename);
  mutt_str_replace (&hdr->content->filename, tmpfile);
}