(timeoutLength->QuadPart < 0 && userTimeout && *userTimeout <= 0) {
      /* Caller has explicitly requested a zero timeout.  */
      timeoutLength->QuadPart = 0;
    }