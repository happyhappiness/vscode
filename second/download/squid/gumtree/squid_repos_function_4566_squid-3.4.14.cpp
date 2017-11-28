int
aclIpAddrNetworkCompare(acl_ip_data * const &p, acl_ip_data * const &q)
{
    Ip::Address A = p->addr1;

    /* apply netmask */
    A.applyMask(q->mask);

    debugs(28,9, "aclIpAddrNetworkCompare: compare: " << p->addr1 << "/" << q->mask << " (" << A << ")  vs " <<
           q->addr1 << "-" << q->addr2 << "/" << q->mask);

    if (q->addr2.isAnyAddr()) {       /* single address check */

        return A.matchIPAddr( q->addr1 );

    } else {                   /* range address check */

        if ( (A >= q->addr1) && (A <= q->addr2) )
            return 0; /* valid. inside range. */
        else
            return A.matchIPAddr( q->addr1 ); /* outside of range, 'less than' */
    }
}