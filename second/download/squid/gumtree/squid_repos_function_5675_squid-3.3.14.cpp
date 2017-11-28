void
IpcIoFile::trackPendingRequest(IpcIoPendingRequest *const pending)
{
    newerRequests->insert(std::make_pair(lastRequestId, pending));
    if (!timeoutCheckScheduled)
        scheduleTimeoutCheck();
}