void _NonAppStop( void )
{
    apr_pool_terminate();

#ifdef USE_WINSOCK
    WSACleanup();
#endif

    unregister_library(gLibId);
    NXMutexFree(gLibLock);
}