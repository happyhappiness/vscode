static void timer(int signum)
{
  (void)signum;

  logmsg("alarm!");

  timeout += rexmtval;
  if (timeout >= maxtimeout)
    exit(1);
#ifdef HAVE_SIGSETJMP
  siglongjmp(timeoutbuf, 1);
#endif
}