static void adjust_date_range (struct tm *min, struct tm *max)
{
  if (min->tm_year > max->tm_year
      || (min->tm_year == max->tm_year && min->tm_mon > max->tm_mon)
      || (min->tm_year == max->tm_year && min->tm_mon == max->tm_mon
	&& min->tm_mday > max->tm_mday))
  {
    int tmp;
    
    tmp = min->tm_year;
    min->tm_year = max->tm_year;
    max->tm_year = tmp;
      
    tmp = min->tm_mon;
    min->tm_mon = max->tm_mon;
    max->tm_mon = tmp;
      
    tmp = min->tm_mday;
    min->tm_mday = max->tm_mday;
    max->tm_mday = tmp;
    
    min->tm_hour = min->tm_min = min->tm_sec = 0;
    max->tm_hour = 23;
    max->tm_min = max->tm_sec = 59;
  }
}