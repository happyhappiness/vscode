static RETSIGTYPE alarm_handler (int sig)
{
  SigAlrm = 1;
}