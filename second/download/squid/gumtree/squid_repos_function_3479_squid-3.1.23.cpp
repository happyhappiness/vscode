void
connNoteUseOfBuffer(ConnStateData* conn, size_t byteCount)
{
    assert(byteCount > 0 && byteCount <= conn->in.notYetUsed);
    conn->in.notYetUsed -= byteCount;
    debugs(33, 5, HERE << "conn->in.notYetUsed = " << conn->in.notYetUsed);
    /*
     * If there is still data that will be used,
     * move it to the beginning.
     */

    if (conn->in.notYetUsed > 0)
        xmemmove(conn->in.buf, conn->in.buf + byteCount,
                 conn->in.notYetUsed);
}