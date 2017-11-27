static void *cgps_thread(void *pData) {
  struct gps_data_t gpsd_conn;
  unsigned int err_count;
  cgps_thread_running = CGPS_TRUE;

  while (CGPS_TRUE) {
    pthread_mutex_lock(&cgps_thread_lock);
    if (cgps_thread_shutdown == CGPS_TRUE) {
      goto quit;
    }
    pthread_mutex_unlock(&cgps_thread_lock);

    err_count = 0;

#if GPSD_API_MAJOR_VERSION > 4
    int status =
        gps_open(cgps_config_data.host, cgps_config_data.port, &gpsd_conn);
#else
    int status =
        gps_open_r(cgps_config_data.host, cgps_config_data.port, &gpsd_conn);
#endif
    if (status < 0) {
      WARNING("gps plugin: connecting to %s:%s failed: %s",
              cgps_config_data.host, cgps_config_data.port, gps_errstr(status));

      // Here we make a pause until a new tentative to connect, we check also if
      // the thread does not need to stop.
      if (cgps_thread_pause(cgps_config_data.pause_connect) == CGPS_FALSE) {
        goto quit;
      }

      continue;
    }

    gps_stream(&gpsd_conn, WATCH_ENABLE | WATCH_JSON | WATCH_NEWSTYLE, NULL);
    gps_send(&gpsd_conn, CGPS_CONFIG);

    while (CGPS_TRUE) {
      pthread_mutex_lock(&cgps_thread_lock);
      if (cgps_thread_shutdown == CGPS_TRUE) {
        goto stop;
      }
      pthread_mutex_unlock(&cgps_thread_lock);

#if GPSD_API_MAJOR_VERSION > 4
      long timeout_us = CDTIME_T_TO_US(cgps_config_data.timeout);
      if (!gps_waiting(&gpsd_conn, (int)timeout_us))
#else
      if (!gps_waiting(&gpsd_conn))
#endif
      {
        continue;
      }

      if (gps_read(&gpsd_conn) == -1) {
        WARNING("gps plugin: incorrect data! (err_count: %d)", err_count);
        err_count++;

        if (err_count > CGPS_MAX_ERROR) {
          // Server is not responding ...
          if (gps_send(&gpsd_conn, CGPS_CONFIG) == -1) {
            WARNING("gps plugin: gpsd seems to be down, reconnecting");
            gps_close(&gpsd_conn);
            break;
          }
          // Server is responding ...
          else {
            err_count = 0;
          }
        }

        continue;
      }

      pthread_mutex_lock(&cgps_data_lock);

      // Number of sats in view:
      cgps_data.sats_used = (gauge_t)gpsd_conn.satellites_used;
      cgps_data.sats_visible = (gauge_t)gpsd_conn.satellites_visible;

      // dilution of precision:
      cgps_data.vdop = NAN;
      cgps_data.hdop = NAN;
      if (cgps_data.sats_used > 0) {
        cgps_data.hdop = gpsd_conn.dop.hdop;
        cgps_data.vdop = gpsd_conn.dop.vdop;
      }

      DEBUG("gps plugin: %.0f sats used (of %.0f visible), hdop = %.3f, vdop = "
            "%.3f",
            cgps_data.sats_used, cgps_data.sats_visible, cgps_data.hdop,
            cgps_data.vdop);

      pthread_mutex_unlock(&cgps_data_lock);
    }
  }

stop:
  DEBUG("gps plugin: thread closing gpsd connection ... ");
  gps_stream(&gpsd_conn, WATCH_DISABLE, NULL);
  gps_close(&gpsd_conn);
quit:
  DEBUG("gps plugin: thread shutting down ... ");
  cgps_thread_running = CGPS_FALSE;
  pthread_mutex_unlock(&cgps_thread_lock);
  pthread_exit(NULL);
}