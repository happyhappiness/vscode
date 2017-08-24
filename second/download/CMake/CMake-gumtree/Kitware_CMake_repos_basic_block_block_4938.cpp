{
      multi->timer_lastcall = none;
      /* there's no timeout now but there was one previously, tell the app to
         disable it */
      return multi->timer_cb(multi, -1, multi->timer_userp);
    }