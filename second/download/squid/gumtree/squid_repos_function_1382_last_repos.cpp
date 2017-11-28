void
helper::syncQueueStats()
{
    if (overloaded()) {
        if (overloadStart) {
            debugs(84, 5, id_name << " still overloaded; dropped " << droppedRequests);
        } else {
            overloadStart = squid_curtime;
            debugs(84, 3, id_name << " became overloaded");
        }
    } else {
        if (overloadStart) {
            debugs(84, 5, id_name << " is no longer overloaded");
            if (droppedRequests) {
                debugs(84, DBG_IMPORTANT, "helper " << id_name <<
                       " is no longer overloaded after dropping " << droppedRequests <<
                       " requests in " << (squid_curtime - overloadStart) << " seconds");
                droppedRequests = 0;
            }
            overloadStart = 0;
        }
    }
}