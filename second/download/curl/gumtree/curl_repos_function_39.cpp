char *max5data(double bytes, char *max5)
{
#define ONE_KILOBYTE 1024
#define ONE_MEGABYTE (1024*1024)

  if(bytes < 100000) {
    sprintf(max5, "%5d", (int)bytes);
    return max5;
  }
  if(bytes < (9999*ONE_KILOBYTE)) {
    sprintf(max5, "%4dk", (int)bytes/ONE_KILOBYTE);
    return max5;
  }
  if(bytes < (100*ONE_MEGABYTE)) {
    /* 'XX.XM' is good as long as we're less than 100 megs */
    sprintf(max5, "%2.1fM", bytes/ONE_MEGABYTE);
    return max5;
  }
  sprintf(max5, "%4dM", (int)bytes/ONE_MEGABYTE);
  return max5;
}