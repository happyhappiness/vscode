  pid_t childPid = fork();

  if (childPid == -1)
    throw torrent::input_error("ExecFile::execute(...) Fork failed.");

  if (childPid == 0) {
    int devNull = open("/dev/null", O_RDWR);
    if (devNull != -1)
      dup2(devNull, 0);
    else
      ::close(0);

