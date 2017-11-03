static void prepend_curdir (char *dst, size_t dstlen)
{
  size_t l;

  if (!dst || !*dst || *dst == '/' || dstlen < 3 ||
      /* XXX bad modularization, these are special to mutt_expand_path() */
      !strchr ("~=+@<>!-^", *dst))
    return;

  dstlen -= 3;
  l = strlen (dst) + 2;
  l = (l > dstlen ? dstlen : l);
  memmove (dst + 2, dst, l);
  dst[0] = '.';
  dst[1] = '/';
  dst[l + 2] = 0;
}