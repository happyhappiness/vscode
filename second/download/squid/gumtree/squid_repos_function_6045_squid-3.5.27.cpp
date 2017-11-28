void
Log::TcpLogger::connectDone(const CommConnectCbParams &params)
{
    if (params.flag != Comm::OK) {
        const double delay = 0.5; // seconds
        if (connectFailures++ % 100 == 0) {
            debugs(MY_DEBUG_SECTION, DBG_IMPORTANT, "tcp:" << remote <<
                   " logger connection attempt #" << connectFailures <<
                   " failed. Will keep trying every " << delay << " seconds.");
        }

        if (!reconnectScheduled) {
            reconnectScheduled = true;
            eventAdd("Log::TcpLogger::DelayedReconnect",
                     Log::TcpLogger::DelayedReconnect,
                     new Pointer(this), 0.5, 0, false);
        }
    } else {
        if (connectFailures > 0) {
            debugs(MY_DEBUG_SECTION, DBG_IMPORTANT, "tcp:" << remote <<
                   " logger connectivity restored after " <<
                   (connectFailures+1) << " attempts.");
            connectFailures = 0;
        }

        Must(!conn);
        conn = params.conn;

        Must(!closer);
        typedef CommCbMemFunT<TcpLogger, CommCloseCbParams> Closer;
        closer = JobCallback(MY_DEBUG_SECTION, 4, Closer, this, Log::TcpLogger::handleClosure);
        comm_add_close_handler(conn->fd, closer);

        writeIfNeeded();
    }
}