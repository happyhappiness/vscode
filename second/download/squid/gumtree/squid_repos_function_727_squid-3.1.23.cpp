static void Win32SockCleanup(void)
{
    if (--s_iInitCount == 0)
        WSACleanup();

    return;
}