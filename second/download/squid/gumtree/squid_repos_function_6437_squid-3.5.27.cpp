int
Icmp::ipHops(int ttl)
{
    if (ttl < 33)
        return 33 - ttl;

    if (ttl < 63)
        return 63 - ttl;        /* 62 = (64+60)/2 */

    if (ttl < 65)
        return 65 - ttl;        /* 62 = (64+60)/2 */

    if (ttl < 129)
        return 129 - ttl;

    if (ttl < 193)
        return 193 - ttl;

    return 256 - ttl;
}