static void timer(int signum)
{
  (void)signum;

  logmsg("alarm!");

  timeout += rexmtval;
  if(timeout >= maxtimeout) {
    if(wrotepidfile) {
      wrotepidfile = 0;
      unlink(pidname);
    }
    if(serverlogslocked) {
      serverlogslocked = 0;
      clear_advisor_read_lock(SERVERLOGS_LOCK);
    }
    exit(1);
  }
#ifdef HAVE_SIGSETJMP
  siglongjmp(timeoutbuf, 1);
#endif
}