static void
mutt_nss_pretty_time (int64 usecs)
{
  struct tm t;
  PRExplodedTime ex;
  char timebuf[128];
  
  PR_ExplodeTime (usecs, PR_LocalTimeParameters, &ex);
  
  t.tm_sec = ex.tm_sec;
  t.tm_min = ex.tm_min;
  t.tm_hour = ex.tm_hour;
  t.tm_mday = ex.tm_mday;
  t.tm_mon = ex.tm_month;
  t.tm_year = ex.tm_year - 1900;	/* PRExplodedTime uses the absolute year */
  t.tm_wday = ex.tm_wday;
  t.tm_yday = ex.tm_yday;
  
  strfcpy (timebuf, asctime (&t), sizeof (timebuf));
  timebuf[strlen (timebuf) - 1] = 0;
  
  addstr (timebuf);
}