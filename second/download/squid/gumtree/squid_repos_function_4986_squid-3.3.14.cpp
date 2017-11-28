void
Ident::Timeout(const CommTimeoutCbParams &io)
{
    debugs(30, 3, HERE << io.conn);
    io.conn->close();
}