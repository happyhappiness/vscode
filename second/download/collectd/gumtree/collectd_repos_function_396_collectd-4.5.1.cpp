static int
handle_raw(const u_char * pkt, int len)
{
    return handle_ip((struct ip *) pkt, len);
}