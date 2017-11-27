static int cgps_thread_pause(cdtime_t pTime) {
  cdtime_t until = cdtime() + pTime;

  pthread_mutex_lock(&cgps_thread_lock);
  pthread_cond_timedwait(&cgps_thread_cond, &cgps_thread_lock,
                         &CDTIME_T_TO_TIMESPEC(until));

  int ret = !cgps_thread_shutdown;

  pthread_mutex_lock(&cgps_thread_lock);
  return ret;
}