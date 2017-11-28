void
addr2oid(IpAddress &addr, oid * Dest)
{
    u_int i ;
    u_char *cp = NULL;
    struct in_addr i4addr;
    struct in6_addr i6addr;
    oid code = addr.IsIPv6()? INETADDRESSTYPE_IPV6  : INETADDRESSTYPE_IPV4 ;
    u_int size = (code == INETADDRESSTYPE_IPV4) ? sizeof(struct in_addr):sizeof(struct in6_addr);
    //  Dest[0] = code ;
    if ( code == INETADDRESSTYPE_IPV4 ) {
        addr.GetInAddr(i4addr);
        cp = (u_char *) &(i4addr.s_addr);
    } else {
        addr.GetInAddr(i6addr);
        cp = (u_char *) &i6addr;
    }
    for ( i=0 ; i < size ; i++) {
        // OID's are in network order
        Dest[i] = *cp++;
    }
    MemBuf tmp;
    debugs(49, 7, "addr2oid: Dest : " << snmpDebugOid(Dest, size, tmp));
}