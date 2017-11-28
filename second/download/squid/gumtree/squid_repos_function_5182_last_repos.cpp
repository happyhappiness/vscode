static int
rfc1035RRUnpack(const char *buf, size_t sz, unsigned int *off, rfc1035_rr * RR)
{
    unsigned short s;
    unsigned int i;
    unsigned short rdlength;
    unsigned int rdata_off;
    if (rfc1035NameUnpack(buf, sz, off, NULL, RR->name, RFC1035_MAXHOSTNAMESZ, 0)) {
        RFC1035_UNPACK_DEBUG;
        memset(RR, '\0', sizeof(*RR));
        return 1;
    }
    /*
     * Make sure the remaining message has enough octets for the
     * rest of the RR fields.
     */
    if ((*off) + 10 > sz) {
        RFC1035_UNPACK_DEBUG;
        memset(RR, '\0', sizeof(*RR));
        return 1;
    }
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    RR->type = ntohs(s);
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    RR->_class = ntohs(s);
    memcpy(&i, buf + (*off), sizeof(i));
    (*off) += sizeof(i);
    RR->ttl = ntohl(i);
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    rdlength = ntohs(s);
    if ((*off) + rdlength > sz) {
        /*
         * We got a truncated packet.  'dnscache' truncates UDP
         * replies at 512 octets, as per RFC 1035.
         */
        RFC1035_UNPACK_DEBUG;
        memset(RR, '\0', sizeof(*RR));
        return 1;
    }
    RR->rdlength = rdlength;
    switch (RR->type) {
#if DNS_CNAME
    case RFC1035_TYPE_CNAME:
#endif
    case RFC1035_TYPE_PTR:
        RR->rdata = (char*)xmalloc(RFC1035_MAXHOSTNAMESZ);
        rdata_off = *off;
        RR->rdlength = 0;   /* Filled in by rfc1035NameUnpack */
        if (rfc1035NameUnpack(buf, sz, &rdata_off, &RR->rdlength, RR->rdata, RFC1035_MAXHOSTNAMESZ, 0)) {
            RFC1035_UNPACK_DEBUG;
            return 1;
        }
        if (rdata_off > ((*off) + rdlength)) {
            /*
             * This probably doesn't happen for valid packets, but
             * I want to make sure that NameUnpack doesn't go beyond
             * the RDATA area.
             */
            RFC1035_UNPACK_DEBUG;
            xfree(RR->rdata);
            memset(RR, '\0', sizeof(*RR));
            return 1;
        }
        break;
    case RFC1035_TYPE_A:
    default:
        RR->rdata = (char*)xmalloc(rdlength);
        memcpy(RR->rdata, buf + (*off), rdlength);
        break;
    }
    (*off) += rdlength;
    assert((*off) <= sz);
    return 0;
}