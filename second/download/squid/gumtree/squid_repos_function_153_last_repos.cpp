void
Win32SockCleanup(void)
{
    WSACleanup();
    return;
}