void
String::setBuffer(char *aBuf, String::size_type aSize)
{
    assert(undefined());
    assert(aSize <= SizeMax_);
    buf_ = aBuf;
    size_ = aSize;
}