static void reset_signal_mask (void) /* {{{ */
{
  sigset_t ss;

  memset (&ss, 0, sizeof (ss));
  sigemptyset (&ss);
  sigprocmask (SIG_SETMASK, &ss, /* old mask = */ NULL);
}