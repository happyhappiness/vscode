void
IpcIoFile::trackPendingRequest(const unsigned int id, IpcIoPendingRequest *const pending)
{
    const std::pair<RequestMap::iterator,bool> result =
        newerRequests->insert(std::make_pair(id, pending));
    Must(result.second); // failures means that id was not unique
    if (!timeoutCheckScheduled)
        scheduleTimeoutCheck();
}