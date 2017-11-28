void
IcmpSquid::DomainPing(Ip::Address &to, const char *domain)
{
#if USE_ICMP
    debugs(37, 4, HERE << "'" << domain << "' (" << to << ")");
    SendEcho(to, S_ICMP_DOM, domain, 0);
#endif
}