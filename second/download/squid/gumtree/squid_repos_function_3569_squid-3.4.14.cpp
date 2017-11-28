bool
ConnStateData::maybeMakeSpaceAvailable()
{
    if (getAvailableBufferLength() < 2) {
        size_t newSize;
        if (in.allocatedSize >= Config.maxRequestBufferSize) {
            debugs(33, 4, "request buffer full: client_request_buffer_max_size=" << Config.maxRequestBufferSize);
            return false;
        }
        if ((newSize=in.allocatedSize * 2) > Config.maxRequestBufferSize) {
            newSize=Config.maxRequestBufferSize;
        }
        in.buf = (char *)memReallocBuf(in.buf, newSize, &in.allocatedSize);
        debugs(33, 2, "growing request buffer: notYetUsed=" << in.notYetUsed << " size=" << in.allocatedSize);
    }
    return true;
}