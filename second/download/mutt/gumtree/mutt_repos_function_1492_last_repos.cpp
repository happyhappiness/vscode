static int check_sig (const char *s, struct line_t *info, int n)
{
  int count = 0;

  while (n > 0 && count <= NumSigLines)
  {
    if (info[n].type != MT_COLOR_SIGNATURE)
      break;
    count++;
    n--;
  }

  if (count == 0)
    return (-1);

  if (count > NumSigLines)
  {
    /* check for a blank line */
    while (*s)
    {
      if (!ISSPACE (*s))
	return 0;
      s++;
    }

    return (-1);
  }

  return (0);
}