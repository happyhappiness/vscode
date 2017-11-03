static int
upNLines (int nlines, struct line_t *info, int cur, int hiding)
{
  while (cur > 0 && nlines > 0)
  {
    cur--;
    if (!hiding || info[cur].type != MT_COLOR_QUOTED)
      nlines--;
  }

  return cur;
}