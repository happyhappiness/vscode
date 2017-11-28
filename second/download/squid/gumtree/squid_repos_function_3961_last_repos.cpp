ACLTimeData&
ACLTimeData::operator=(ACLTimeData const &old)
{
    weekbits = old.weekbits;
    start = old.start;
    stop = old.stop;
    next = NULL;

    if (old.next)
        next = (ACLTimeData *)old.next->clone();

    return *this;
}