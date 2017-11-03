static void write_safe_address (FILE *fp, char *s)
{
  while (*s)
  {
    if (*s == '\\' || *s == '`' || *s == '\'' || *s == '"'
	|| *s == '$')
      fputc ('\\', fp);
    fputc (*s, fp);
    s++;
  }
}