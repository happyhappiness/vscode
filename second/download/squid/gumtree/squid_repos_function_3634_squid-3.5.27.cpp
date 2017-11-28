static void
connStripBufferWhitespace (ConnStateData * conn)
{
    // XXX: kill this whole function.
    while (!conn->in.buf.isEmpty() && xisspace(conn->in.buf.at(0))) {
        conn->in.buf.consume(1);
    }
}