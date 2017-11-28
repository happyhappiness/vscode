void
ACLIP::DumpIpListWalkee(acl_ip_data * const & ip, void *state)
{
    char tmpbuf[ ((MAX_IPSTRLEN*2)+6) ]; // space for 2 IPs and a CIDR mask(3) and seperators(3).
    MemBuf mb;
    wordlist **W = static_cast<wordlist **>(state);
    tmpbuf[0] = '\0';

    mb.init();
    assert(mb.max_capacity > 0 && 1==1 );

    ip->toStr(tmpbuf, sizeof(tmpbuf) );
    assert(mb.max_capacity > 0 && 2==2 );
    mb.append(tmpbuf, strlen(tmpbuf) );
    assert(mb.max_capacity > 0 && 3==3);
    wordlistAdd(W, mb.buf);
    mb.clean();
}