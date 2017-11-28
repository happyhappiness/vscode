void
ConnStateData::consumeInput(const size_t byteCount)
{
    assert(byteCount > 0 && byteCount <= inBuf.length());
    inBuf.consume(byteCount);
    debugs(33, 5, "inBuf has " << inBuf.length() << " unused bytes");
}