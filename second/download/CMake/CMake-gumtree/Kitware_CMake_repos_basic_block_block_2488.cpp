{
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;
    startupInfo.hStdInput = hIn;
    startupInfo.hStdOutput = hOut;
    startupInfo.hStdError = hErr;
    bInheritHandles = TRUE;
  }