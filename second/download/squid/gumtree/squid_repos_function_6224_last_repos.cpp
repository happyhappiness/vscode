void
Log::TcpLogger::writeDone(const CommIoCbParams &io)
{
    writeScheduled = false;
    if (io.flag == Comm::ERR_CLOSING) {
        debugs(MY_DEBUG_SECTION, 7, "closing");
        // do nothing here -- our comm_close_handler will be called to clean up
    } else if (io.flag != Comm::OK) {
        debugs(MY_DEBUG_SECTION, 2, "write failure: " << xstrerr(io.xerrno));
        // keep the first buffer (the one we failed to write)
        disconnect();
        doConnect();
    } else {
        debugs(MY_DEBUG_SECTION, 5, "write successful");

        Must(!buffers.empty()); // we had a buffer to write
        const MemBlob::Pointer &written = buffers.front();
        const size_t writtenSize = static_cast<size_t>(written->size);
        // and we wrote the whole buffer
        Must(io.size == writtenSize);
        Must(bufferedSize >= writtenSize);
        bufferedSize -= writtenSize;

        buffers.pop_front();

        if (flushDebt > io.size)
            flushDebt -= io.size;
        else
            flushDebt = 0; // wrote everything we owed (or more)

        writeIfNeeded();
    }
}