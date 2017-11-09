static void
print_utf8 (FILE *fp, const char *buf, size_t len)
{
  char *tstr;

  tstr = safe_malloc (len+1);
  memcpy (tstr, buf, len);
  tstr[len] = 0;

  /* fromcode "utf-8" is sure, so we don't want
   * charset-hook corrections: flags must be 0.
   */
  mutt_convert_string (&tstr, "utf-8", Charset, 0);
  fputs (tstr, fp);
  FREE (&tstr);
}