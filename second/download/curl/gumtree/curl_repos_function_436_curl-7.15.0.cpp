static
RETSIGTYPE alarmfunc(int sig)
{
  /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
  (void)sig;
#ifdef HAVE_SIGSETJMP
  siglongjmp(curl_jmpenv, 1);
#endif
  return;
}