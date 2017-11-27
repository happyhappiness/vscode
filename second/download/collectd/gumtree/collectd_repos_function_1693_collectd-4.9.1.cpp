static char *lcc_strescape (char *dest, const char *src, size_t dest_size) /* {{{ */
{
  size_t dest_pos;
  size_t src_pos;

  dest_pos = 0;
  src_pos = 0;

  assert (dest_size >= 3);

  dest[dest_pos] = '"';
  dest_pos++;

  while (42)
  {
    if ((dest_pos == (dest_size - 2))
        || (src[src_pos] == 0))
      break;

    if ((src[src_pos] == '"') || (src[src_pos] == '\\'))
    {
      /* Check if there is enough space for both characters.. */
      if (dest_pos == (dest_size - 3))
        break;

      dest[dest_pos] = '\\';
      dest_pos++;
    }

    dest[dest_pos] = src[src_pos];
    dest_pos++;
    src_pos++;
  }

  assert (dest_pos <= (dest_size - 2));

  dest[dest_pos] = '"';
  dest_pos++;

  dest[dest_pos] = 0;
  dest_pos++;
  src_pos++;

  return (dest);
}