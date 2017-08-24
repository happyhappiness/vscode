{
      /* There is some time left.  */
      timeoutLength->tv_sec = timeLeft.tv_sec;
      timeoutLength->tv_usec = timeLeft.tv_usec;
      return 0;
    }