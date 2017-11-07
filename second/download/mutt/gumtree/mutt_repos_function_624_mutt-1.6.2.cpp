static void be_free_memory (char **buf, int buflen)
{
  while (buflen-- > 0)
    FREE (&buf[buflen]);
  if (buf)
    FREE (&buf);
}