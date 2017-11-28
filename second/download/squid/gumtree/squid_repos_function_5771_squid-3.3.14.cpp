static const char *
IcmpPacketType(uint8_t v)
{
    static const char *icmpPktStr[] = {
        "Echo Reply",
        "ICMP 1",
        "ICMP 2",
        "Destination Unreachable",
        "Source Quench",
        "Redirect",
        "ICMP 6",
        "ICMP 7",
        "Echo",
        "ICMP 9",
        "ICMP 10",
        "Time Exceeded",
        "Parameter Problem",
        "Timestamp",
        "Timestamp Reply",
        "Info Request",
        "Info Reply",
        "Out of Range Type"
    };

    if (v > 17) {
        static char buf[50];
        snprintf(buf, sizeof(buf), "ICMP %u (invalid)", v);
        return buf;
    }

    return icmpPktStr[v];
}