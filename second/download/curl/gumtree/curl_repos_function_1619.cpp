static
RETSIGTYPE alarmfunc(int sig)
{
  /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
  (void)sig;
  siglongjmp(curl_jmpenv, 1);
  return;
}