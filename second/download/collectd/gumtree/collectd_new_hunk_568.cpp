
    if (vl->time != last_time)
    {
      printf ("%i values have been sent.\n", values_sent);

      /* Check if we need to sleep */
      double now = dtime ();

      while (now < vl->time)
      {
        /* 1 / 100 second */
        struct timespec ts = { 0, 10000000 };

        ts.tv_sec = (time_t) now;
        ts.tv_nsec = (long) ((now - ((double) ts.tv_sec)) * 1e9);

        nanosleep (&ts, /* remaining = */ NULL);
        now = dtime ();

        if (!loop)
          break;
      }
      last_time = vl->time;
    }
