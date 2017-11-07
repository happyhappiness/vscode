static void
append_line (struct line_t *lineInfo, int n, int cnt)
{
  int m;

  lineInfo[n+1].type = lineInfo[n].type;
  (lineInfo[n+1].syntax)[0].color = (lineInfo[n].syntax)[0].color;
  lineInfo[n+1].continuation = 1;

  /* find the real start of the line */
  for (m = n; m >= 0; m--)
    if (lineInfo[m].continuation == 0) break;

  (lineInfo[n+1].syntax)[0].first = m;
  (lineInfo[n+1].syntax)[0].last = (lineInfo[n].continuation) ? 
    cnt + (lineInfo[n].syntax)[0].last : cnt;
}