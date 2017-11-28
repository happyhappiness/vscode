SBuf
acl_ip_data::toSBuf() const
{
    const int bufsz = MAX_IPSTRLEN*2+6;
    static char tmpbuf[ bufsz ];
    toStr(tmpbuf,bufsz);
    return SBuf(tmpbuf);
}