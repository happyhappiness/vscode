{
    /* Calculate the remaining time.  */
    kwsysProcessTime currentTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime timeLeft =
      kwsysProcessTimeSubtract(*timeoutTime, currentTime);
    if (timeLeft.tv_sec < 0 && userTimeout && *userTimeout <= 0) {
      /* Caller has explicitly requested a zero timeout.  */
      timeLeft.tv_sec = 0;
      timeLeft.tv_usec = 0;
    }

    if (timeLeft.tv_sec < 0 ||
        (timeLeft.tv_sec == 0 && timeLeft.tv_usec == 0 && zeroIsExpired)) {
      /* Timeout has already expired.  */
      return 1;
    } else {
      /* There is some time left.  */
      timeoutLength->tv_sec = timeLeft.tv_sec;
      timeoutLength->tv_usec = timeLeft.tv_usec;
      return 0;
    }
  }