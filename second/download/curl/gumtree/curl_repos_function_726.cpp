void _NonAppStop( void )
{
  (void) unregister_library(gLibId);
  NXMutexFree(gLibLock);
}