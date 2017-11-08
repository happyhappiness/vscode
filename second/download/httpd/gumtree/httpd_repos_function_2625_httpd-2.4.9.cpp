void _NonAppStop( void )
{
#ifdef USE_WINSOCK
    WSACleanup();
#else
    return;
#endif
}