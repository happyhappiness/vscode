void
CossSwapDir::startMembuf()
{
    CossMemBuf *newmb;
    newmb = createMemBuf(current_offset, -1, NULL);
    assert(!current_membuf);
    current_membuf = newmb;
}