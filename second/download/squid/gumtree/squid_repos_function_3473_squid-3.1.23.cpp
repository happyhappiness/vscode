int
ConnStateData::getAvailableBufferLength() const
{
    int result = in.allocatedSize - in.notYetUsed - 1;
    assert (result >= 0);
    return result;
}