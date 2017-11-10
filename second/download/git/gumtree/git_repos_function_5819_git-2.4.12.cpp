static int
re_search_2_stub (struct re_pattern_buffer *bufp,
		  const char *string1, int length1,
		  const char *string2, int length2, int start,
		  int range, struct re_registers *regs,
		  int stop, int ret_len)
{
  const char *str;
  int rval;
  int len = length1 + length2;
  int free_str = 0;

  if (BE (length1 < 0 || length2 < 0 || stop < 0, 0))
    return -2;

  /* Concatenate the strings.  */
  if (length2 > 0)
    if (length1 > 0)
      {
	char *s = re_malloc (char, len);

	if (BE (s == NULL, 0))
	  return -2;
	memcpy (s, string1, length1);
	memcpy (s + length1, string2, length2);
	str = s;
	free_str = 1;
      }
    else
      str = string2;
  else
    str = string1;

  rval = re_search_stub (bufp, str, len, start, range, stop, regs, ret_len);
  if (free_str)
    re_free ((char *) str);
  return rval;
}