static RETSIGTYPE exit_signal_handler(int signum)
{
  int old_errno = ERRNO;
  if(got_exit_signal == 0) {
    got_exit_signal = 1;
    exit_signal = signum;
  }
  (void)signal(signum, exit_signal_handler);
  SET_ERRNO(old_errno);
}