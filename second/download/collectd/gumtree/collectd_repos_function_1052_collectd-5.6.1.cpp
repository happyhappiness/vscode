static int cgps_thread_pause(cdtime_t pTime)
{
  cdtime_t now;
  now = cdtime ();
  struct timespec pause_th;
  CDTIME_T_TO_TIMESPEC (MS_TO_CDTIME_T(10), &pause_th);
  while (CGPS_TRUE)
  {
    if ( (cdtime () - now) > pTime )
    {
      break;
    }

    pthread_mutex_lock (&cgps_thread_lock);
    if (cgps_thread_shutdown == CGPS_TRUE)
    {
      return CGPS_FALSE;
    }
    pthread_mutex_unlock (&cgps_thread_lock);
    nanosleep (&pause_th, NULL);
 }

 return CGPS_TRUE;
}