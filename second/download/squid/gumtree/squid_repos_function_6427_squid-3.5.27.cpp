void
IcmpSquid::Close(void)
{
#if USE_ICMP

    if (icmp_sock < 0)
        return;

    debugs(37, DBG_IMPORTANT, HERE << "Closing Pinger socket on FD " << icmp_sock);

#if _SQUID_WINDOWS_

    send(icmp_sock, (const void *) "$shutdown\n", 10, 0);

#endif

    comm_close(icmp_sock);

#if _SQUID_WINDOWS_

    if (hIpc) {
        if (WaitForSingleObject(hIpc, 12000) != WAIT_OBJECT_0) {
            getCurrentTime();
            debugs(37, DBG_CRITICAL, HERE << "WARNING: (pinger," << pid << ") didn't exit in 12 seconds");
        }

        CloseHandle(hIpc);
    }

#endif
    icmp_sock = -1;

#endif
}