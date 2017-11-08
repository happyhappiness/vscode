static void timer(int signum)
{
  (void)signum;

  logmsg("alarm!");

  timeout += rexmtval;
  if (timeout >= maxtimeout)
    exit(1);
  siglongjmp(timeoutbuf, 1);
}