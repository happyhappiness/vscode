static
RETSIGTYPE alarmfunc(int signal)
{
  /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
  (void)signal;
#ifdef HAVE_SIGSETJMP
  siglongjmp(curl_jmpenv, 1);
#endif
  return;
}