static void
connStripBufferWhitespace (ConnStateData * conn)
{
    while (conn->in.notYetUsed > 0 && xisspace(conn->in.buf[0])) {
        xmemmove(conn->in.buf, conn->in.buf + 1, conn->in.notYetUsed - 1);
        --conn->in.notYetUsed;
    }
}