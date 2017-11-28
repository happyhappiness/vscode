void
IpcIoFile::checkTimeouts()
{
    timeoutCheckScheduled = false;

    // last chance to recover in case a notification message was lost, etc.
    const RequestMap::size_type timeoutsBefore = olderRequests->size();
    HandleResponses("before timeout");
    const RequestMap::size_type timeoutsNow = olderRequests->size();

    if (timeoutsBefore > timeoutsNow) { // some requests were rescued
        // notification message lost or significantly delayed?
        debugs(47, DBG_IMPORTANT, "WARNING: communication with " << dbName <<
               " may be too slow or disrupted for about " <<
               Timeout << "s; rescued " << (timeoutsBefore - timeoutsNow) <<
               " out of " << timeoutsBefore << " I/Os");
    }

    if (timeoutsNow) {
        debugs(47, DBG_IMPORTANT, "WARNING: abandoning " <<
               timeoutsNow << ' ' << dbName << " I/Os after at least " <<
               Timeout << "s timeout");
    }

    // any old request would have timed out by now
    typedef RequestMap::const_iterator RMCI;
    for (RMCI i = olderRequests->begin(); i != olderRequests->end(); ++i) {
        IpcIoPendingRequest *const pending = i->second;

        const unsigned int requestId = i->first;
        debugs(47, 7, HERE << "disker timeout; ipcIo" <<
               KidIdentifier << '.' << requestId);

        pending->completeIo(NULL); // no response
        delete pending; // XXX: leaking if throwing
    }
    olderRequests->clear();

    swap(olderRequests, newerRequests); // switches pointers around
    if (!olderRequests->empty() && !timeoutCheckScheduled)
        scheduleTimeoutCheck();
}