void
ClientHttpRequest::callException(const std::exception &ex)
{
    if (const auto clientConn = getConn() ? getConn()->clientConnection : nullptr) {
        if (Comm::IsConnOpen(clientConn)) {
            debugs(85, 3, "closing after exception: " << ex.what());
            clientConn->close(); // initiate orderly top-to-bottom cleanup
            return;
        }
    }
    debugs(85, DBG_IMPORTANT, "ClientHttpRequest exception without connection. Ignoring " << ex.what());
    // XXX: Normally, we mustStop() but we cannot do that here because it is
    // likely to leave Http::Stream and ConnStateData with a dangling http
    // pointer. See r13480 or XXX in Http::Stream class description.
}