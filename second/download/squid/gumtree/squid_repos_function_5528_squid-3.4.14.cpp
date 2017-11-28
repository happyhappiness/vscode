void Log::TcpLogger::writeIfPossible()
{
    debugs(MY_DEBUG_SECTION, 7, "guards: " << (!writeScheduled) <<
           (bufferedSize > 0) << (conn != NULL) <<
           (conn != NULL && !fd_table[conn->fd].closing()) << " buffered: " <<
           bufferedSize << '/' << buffers.size());

    // XXX: Squid shutdown sequence starts closing our connection before
    // calling LogfileClose, leading to loss of log records during shutdown.
    if (!writeScheduled && bufferedSize > 0 && conn != NULL &&
            !fd_table[conn->fd].closing()) {
        debugs(MY_DEBUG_SECTION, 5, "writing first buffer");

        typedef CommCbMemFunT<TcpLogger, CommIoCbParams> WriteDialer;
        AsyncCall::Pointer callback = JobCallback(MY_DEBUG_SECTION, 5, WriteDialer, this, Log::TcpLogger::writeDone);
        const MemBlob::Pointer &buffer = buffers.front();
        Comm::Write(conn, buffer->mem, buffer->size, callback, NULL);
        writeScheduled = true;
    }
}