static unsigned char *
dump_char_size(char *c, unsigned char *d, int *off, ssize_t size, int convert)
{
  char *p = c;

  if (c == NULL)
  {
    size = 0;
    d = dump_int(size, d, off);
    return d;
  }

  if (convert && !is_ascii (c, size)) {
    p = mutt_substrdup (c, c + size);
    if (mutt_convert_string (&p, Charset, "utf-8", 0) == 0) {
      c = p;
      size = mutt_strlen (c) + 1;
    }
  }

  d = dump_int(size, d, off);
  lazy_realloc(&d, *off + size);
  memcpy(d + *off, p, size);
  *off += size;

  if (p != c)
    FREE(&p);

  return d;
}