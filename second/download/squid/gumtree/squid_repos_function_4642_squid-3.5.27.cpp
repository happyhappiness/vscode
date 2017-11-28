SBufList
ACLTimeData::dump() const
{
    SBufList sl;
    const ACLTimeData *t = this;

    while (t != NULL) {
        SBuf s;
        s.Printf("%c%c%c%c%c%c%c %02d:%02d-%02d:%02d",
                 t->weekbits & ACL_SUNDAY ? 'S' : '-',
                 t->weekbits & ACL_MONDAY ? 'M' : '-',
                 t->weekbits & ACL_TUESDAY ? 'T' : '-',
                 t->weekbits & ACL_WEDNESDAY ? 'W' : '-',
                 t->weekbits & ACL_THURSDAY ? 'H' : '-',
                 t->weekbits & ACL_FRIDAY ? 'F' : '-',
                 t->weekbits & ACL_SATURDAY ? 'A' : '-',
                 t->start / 60, t->start % 60, t->stop / 60, t->stop % 60);
        sl.push_back(s);
        t = t->next;
    }

    return sl;
}