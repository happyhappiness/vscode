static long
difftm (struct tm *a, struct tm *b)
{
  int ay = a->tm_year + (TM_YEAR_ORIGIN - 1);
  int by = b->tm_year + (TM_YEAR_ORIGIN - 1);
  long days = (
  /* difference in day of year */
		a->tm_yday - b->tm_yday
  /* + intervening leap days */
		+ ((ay >> 2) - (by >> 2))
		- (ay / 100 - by / 100)
		+ ((ay / 100 >> 2) - (by / 100 >> 2))
  /* + difference in years * 365 */
		+ (long) (ay - by) * 365
  );
  return (60 * (60 * (24 * days + (a->tm_hour - b->tm_hour))
		+ (a->tm_min - b->tm_min))
	  + (a->tm_sec - b->tm_sec));
}