int main(void)
{
  /* initialize any globals here... */

  /* do this if any global initializing was done
  SynchronizeStart();
  */
  ExitThread(TSR_THREAD, 0);
  return 0;
}