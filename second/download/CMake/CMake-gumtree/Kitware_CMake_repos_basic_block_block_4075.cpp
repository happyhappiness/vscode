f(!alarm_set ||
       ((alarm_set >= 0x80000000) && (prev_alarm < 0x80000000)) ) {
      /* if the alarm time-left reached zero or turned "negative" (counted
         with unsigned values), we should fire off a SIGALRM here, but we
         won't, and zero would be to switch it off so we never set it to
         less than 1! */
      alarm(1);
      rc = CURLRESOLV_TIMEDOUT;
      failf(data, "Previous alarm fired off!");
    }
    else
      alarm((unsigned int)alarm_set)