MemBuf *
HttpReply::pack() const
{
    MemBuf *mb = new MemBuf;
    mb->init();
    packInto(mb);
    return mb;
}