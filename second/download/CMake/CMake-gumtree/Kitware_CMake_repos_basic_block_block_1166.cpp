{
    kwsysProcessTime userEndTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime difference =
      kwsysProcessTimeSubtract(userEndTime, userStartTime);
    double d = kwsysProcessTimeToDouble(difference);
    *userTimeout -= d;
    if (*userTimeout < 0) {
      *userTimeout = 0;
    }
  }