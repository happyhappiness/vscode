void _NonAppStop( void )
{
    apr_pool_terminate();

    WSACleanup();

    unregister_library(gLibId);
    NXMutexFree(gLibLock);
}