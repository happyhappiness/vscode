void
IcmpPinger::Close(void)
{
#ifdef _SQUID_MSWIN_

    shutdown(icmp_sock, SD_BOTH);
    close(icmp_sock);
    icmp_sock = -1;
#endif

    /* also shutdown the helper engines */
    icmp4.Close();
    icmp6.Close();
}