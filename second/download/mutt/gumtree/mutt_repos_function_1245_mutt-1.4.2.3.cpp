static void
argz_stringify__ (argz, len, sep)
     char *argz;
     size_t len;
     int sep;
{
  while (len > 0)
    {
      size_t part_len = strlen (argz);
      argz += part_len;
      len -= part_len + 1;
      if (len > 0)
	*argz++ = sep;
    }
}