void
Icmp::Log(const IpAddress &addr, const u_int8_t type, const char* pkt_str, const int rtt, const int hops)
{
    debugs(42, 2, "pingerLog: " << std::setw(9) << current_time.tv_sec  <<
           "." << std::setfill('0') << std::setw(6) <<
           current_time.tv_usec  << " " << std::left << std::setfill(' ') <<
           std::setw(45) << addr  << " " << type  <<
           " " << std::setw(15) << pkt_str << " " << rtt  <<
           "ms " << hops  << " hops");
}