static const char *
IcmpPacketType(uint8_t v)
{
    // NP: LowPktStr is for codes 0-127
    static const char *icmp6LowPktStr[] = {
        "ICMPv6 0",			// 0
        "Destination Unreachable",	// 1 - RFC2463
        "Packet Too Big", 		// 2 - RFC2463
        "Time Exceeded",		// 3 - RFC2463
        "Parameter Problem",		// 4 - RFC2463
    };

    // low codes 1-4 registered
    if (0 < v && v < 5)
        return icmp6LowPktStr[(int)(v&0x7f)];

    // NP: HighPktStr is for codes 128-255
    static const char *icmp6HighPktStr[] = {
        "Echo Request",					// 128 - RFC2463
        "Echo Reply",					// 129 - RFC2463
        "Multicast Listener Query",			// 130 - RFC2710
        "Multicast Listener Report",			// 131 - RFC2710
        "Multicast Listener Done",			// 132 - RFC2710
        "Router Solicitation",				// 133 - RFC4861
        "Router Advertisement",				// 134 - RFC4861
        "Neighbor Solicitation",			// 135 - RFC4861
        "Neighbor Advertisement",			// 136 - RFC4861
        "Redirect Message",				// 137 - RFC4861
        "Router Renumbering",				// 138 - Crawford
        "ICMP Node Information Query",			// 139 - RFC4620
        "ICMP Node Information Response",		// 140 - RFC4620
        "Inverse Neighbor Discovery Solicitation",	// 141 - RFC3122
        "Inverse Neighbor Discovery Advertisement",	// 142 - RFC3122
        "Version 2 Multicast Listener Report",		// 143 - RFC3810
        "Home Agent Address Discovery Request",		// 144 - RFC3775
        "Home Agent Address Discovery Reply",		// 145 - RFC3775
        "Mobile Prefix Solicitation",			// 146 - RFC3775
        "Mobile Prefix Advertisement",			// 147 - RFC3775
        "Certification Path Solicitation",		// 148 - RFC3971
        "Certification Path Advertisement",		// 149 - RFC3971
        "ICMP Experimental (150)",			// 150 - RFC4065
        "Multicast Router Advertisement",		// 151 - RFC4286
        "Multicast Router Solicitation",		// 152 - RFC4286
        "Multicast Router Termination",			// 153 - [RFC4286]
    };

    // high codes 127-153 registered
    if (127 < v && v < 154)
        return icmp6HighPktStr[(int)(v&0x7f)];

    // give all others a generic display
    static char buf[50];
    snprintf(buf, sizeof(buf), "ICMPv6 %u", v);
    return buf;
}