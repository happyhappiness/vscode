static int
sortPeerByRtt(const void *A, const void *B)
{
    const net_db_peer *p1 = (net_db_peer *)A;
    const net_db_peer *p2 = (net_db_peer *)B;

    if (p1->rtt > p2->rtt)
        return 1;
    else if (p1->rtt < p2->rtt)
        return -1;
    else
        return 0;
}