
    if (vl->time != last_time)
    {
      printf ("%i values have been sent.\n", values_sent);

      /* Check if we need to sleep */
      time_t now = time (NULL);

      while (now < vl->time)
      {
        /* 1 / 100 second */
        struct timespec ts = { 0, 10000000 };
        nanosleep (&ts, /* remaining = */ NULL);
        now = time (NULL);

        if (!loop)
          break;
      }
      last_time = vl->time;
    }
