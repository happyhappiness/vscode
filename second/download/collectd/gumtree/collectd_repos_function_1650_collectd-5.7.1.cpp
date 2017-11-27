static void check_respawn(void) {
  time_t t = time(NULL);

  static time_t timestamp = 0;
  static int counter = 0;

  if ((t - 120) < timestamp)
    ++counter;
  else {
    timestamp = t;
    counter = 0;
  }

  if (10 < counter) {
    unsigned int time_left = 300;

    syslog(LOG_ERR, "Error: collectd is respawning too fast - "
                    "disabled for %i seconds",
           time_left);

    while ((0 < (time_left = sleep(time_left))) && (0 == loop))
      ;
  }
  return;
}