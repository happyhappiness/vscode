StoreMeta& StoreMeta::operator=(const StoreMeta &s)
{
    length=s.length;
    value=s.value;
    next=s.next;
    return *this;
}