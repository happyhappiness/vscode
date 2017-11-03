void mutt_sleep (short s)
{
  if (SleepTime > s)
    sleep (SleepTime);
  else if (s)
    sleep(s);
}