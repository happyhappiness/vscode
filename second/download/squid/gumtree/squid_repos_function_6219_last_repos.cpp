void
Log::TcpLogger::appendChunk(const char *chunk, const size_t len)
{
    Must(len <= IoBufSize);
    // add a buffer if there is not one that can accomodate len bytes
    bool addBuffer = buffers.empty() ||
                     (buffers.back()->size+len > IoBufSize);
    // also add a buffer if there is only one and that one is being written
    addBuffer = addBuffer || (writeScheduled && buffers.size() == 1);

    if (addBuffer) {
        buffers.push_back(new MemBlob(IoBufSize));
        debugs(MY_DEBUG_SECTION, 7, "added buffer #" << buffers.size());
    }

    Must(!buffers.empty());
    buffers.back()->append(chunk, len);
    bufferedSize += len;
}