void _NonAppStop( void )
{
#ifdef USE_WINSOCK
    WSACleanup();
#else
    return;0;
#endif
}