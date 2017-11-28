static void
kickDelayedRequest()
{
    if (TheDelayedRequests.empty())
        return; // no pending requests to resume

    debugs(54, 3, "resuming with " << TheSharedListenRequestMap.size() <<
           " active + " << TheDelayedRequests.size() << " delayed requests");

    SendSharedListenRequest(*TheDelayedRequests.begin());
    TheDelayedRequests.pop_front();
}