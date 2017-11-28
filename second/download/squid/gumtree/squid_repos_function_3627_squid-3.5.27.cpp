void
ConnStateData::consumeInput(const size_t byteCount)
{
    assert(byteCount > 0 && byteCount <= in.buf.length());
    in.buf.consume(byteCount);
    debugs(33, 5, "in.buf has " << in.buf.length() << " unused bytes");
}