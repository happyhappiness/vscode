static RETSIGTYPE exit_signal_handler(int signum)
{
  int old_errno = errno;
  if(got_exit_signal == 0) {
    got_exit_signal = 1;
    exit_signal = signum;
  }
  (void)signal(signum, exit_signal_handler);
  errno = old_errno;
}