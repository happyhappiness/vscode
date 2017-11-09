static void
restore_char(char **c, const unsigned char *d, int *off, int convert)
{
  unsigned int size;
  restore_int(&size, d, off);

  if (size == 0)
  {
    *c = NULL;
    return;
  }

  *c = safe_malloc(size);
  memcpy(*c, d + *off, size);
  if (convert && !is_ascii (*c, size)) {
    char *tmp = safe_strdup (*c);
    if (mutt_convert_string (&tmp, "utf-8", Charset, 0) == 0) {
      mutt_str_replace (c, tmp);
    } else {
      FREE(&tmp);
    }
  }
  *off += size;
}