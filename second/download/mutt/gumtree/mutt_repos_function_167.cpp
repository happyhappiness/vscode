int mutt_copy_bytes (FILE *in, FILE *out, size_t size)
{
  char buf[2048];
  size_t chunk;

  while (size > 0)
  {
    chunk = (size > sizeof (buf)) ? sizeof (buf) : size;
    if ((chunk = fread (buf, 1, chunk, in)) < 1)
      break;
    if (fwrite (buf, 1, chunk, out) != chunk)
    {
      /* dprint (1, (debugfile, "mutt_copy_bytes(): fwrite() returned short byte count\n")); */
      return (-1);
    }
    size -= chunk;
  }

  return 0;
}