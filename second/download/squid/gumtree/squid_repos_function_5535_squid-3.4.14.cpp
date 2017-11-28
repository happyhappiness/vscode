void
Log::TcpLogger::delayedReconnect()
{
    Must(reconnectScheduled);
    Must(!conn);
    reconnectScheduled = false;
    doConnect();
}