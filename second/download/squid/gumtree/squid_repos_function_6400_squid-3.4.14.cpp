const char*
Ipc::Inquirer::status() const
{
    static MemBuf buf;
    buf.reset();
    buf.Printf(" [request->requestId %u]", request->requestId);
    buf.terminate();
    return buf.content();
}