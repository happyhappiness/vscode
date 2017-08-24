{
    kwsysProcessTime currentTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime userTimeoutLength =
      kwsysProcessTimeFromDouble(*userTimeout);
    kwsysProcessTime userTimeoutTime =
      kwsysProcessTimeAdd(currentTime, userTimeoutLength);
    if (timeoutTime->QuadPart < 0 ||
        kwsysProcessTimeLess(userTimeoutTime, *timeoutTime)) {
      *timeoutTime = userTimeoutTime;
      return 1;
    }
  }