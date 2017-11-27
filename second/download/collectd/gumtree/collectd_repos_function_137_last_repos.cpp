static void reset_signal_mask(void) /* {{{ */
{
  sigset_t ss;

  sigemptyset(&ss);
  sigprocmask(SIG_SETMASK, &ss, /* old mask = */ NULL);
}