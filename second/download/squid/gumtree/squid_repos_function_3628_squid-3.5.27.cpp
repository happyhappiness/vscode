void
connNoteUseOfBuffer(ConnStateData* conn, size_t byteCount)
{
    conn->consumeInput(byteCount);
}