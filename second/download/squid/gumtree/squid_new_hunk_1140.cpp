    }
}

/// This is our comm_close_handler. It is called when some external force
/// (e.g., reconfigure or shutdown) is closing the connection (rather than us).
void
Log::TcpLogger::handleClosure(const CommCloseCbParams &)
{
    assert(inCall != NULL);
    closer = NULL;
    conn = NULL;
    // in all current use cases, we should not try to reconnect
    mustStop("Log::TcpLogger::handleClosure");
