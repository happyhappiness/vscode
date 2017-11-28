bool
helper::prepSubmit()
{
    // re-sync for the configuration may have changed since the last submission
    syncQueueStats();

    // Nothing special to do if the new request does not overload (i.e., the
    // queue is not even full yet) or only _starts_ overloading this helper
    // (i.e., the queue is currently at its limit).
    if (!overloaded())
        return true;

    if (squid_curtime - overloadStart <= 180)
        return true; // also OK: overload has not persisted long enough to panic

    if (childs.onPersistentOverload == Helper::ChildConfig::actDie)
        fatalf("Too many queued %s requests; see on-persistent-overload.", id_name);

    if (!droppedRequests) {
        debugs(84, DBG_IMPORTANT, "WARNING: dropping requests to overloaded " <<
               id_name << " helper configured with on-persistent-overload=err");
    }
    ++droppedRequests;
    debugs(84, 3, "failed to send " << droppedRequests << " helper requests to " << id_name);
    return false;
}