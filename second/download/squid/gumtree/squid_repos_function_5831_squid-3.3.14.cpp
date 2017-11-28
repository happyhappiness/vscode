void
Icmp::Close()
{
#if USE_ICMP
    if (icmp_sock > 0)
        close(icmp_sock);
    icmp_sock = -1;
    icmp_ident = 0;
#endif
}