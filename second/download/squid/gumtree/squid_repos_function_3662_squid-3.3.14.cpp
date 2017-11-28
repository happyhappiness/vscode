static void
usage(void)
{
    fprintf(stderr, "usage: dnsserver -hv -s nameserver\n"
            "\t-h             Help\n"
            "\t-v             Version\n"
            "\t-s nameserver  Specify alternate name server(s).  'nameserver'\n"
            "\t               must be an IPv4 address, -s option may be repeated\n"
           );
}