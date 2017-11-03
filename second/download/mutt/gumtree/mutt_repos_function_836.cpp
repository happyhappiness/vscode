static int isLeapYearFeb (struct tm *tm)
{
  if (tm->tm_mon == 1)
  {
    int y = tm->tm_year + 1900;
    return (((y & 3) == 0) && (((y % 100) != 0) || ((y % 400) == 0)));
  }
  return (0);
}