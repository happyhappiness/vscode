void
CollapsedForwarding::Broadcast(const StoreEntry &e)
{
    if (!queue.get())
        return;

    if (!e.mem_obj || e.mem_obj->xitTable.index < 0 ||
            !Store::Root().transientReaders(e)) {
        debugs(17, 7, "nobody reads " << e);
        return;
    }

    CollapsedForwardingMsg msg;
    msg.sender = KidIdentifier;
    msg.xitIndex = e.mem_obj->xitTable.index;

    debugs(17, 5, e << " to " << Config.workers << "-1 workers");

    // TODO: send only to workers who are waiting for data
    for (int workerId = 1; workerId <= Config.workers; ++workerId) {
        try {
            if (workerId != KidIdentifier && queue->push(workerId, msg))
                Notify(workerId);
        } catch (const Queue::Full &) {
            debugs(17, DBG_IMPORTANT, "ERROR: Collapsed forwarding " <<
                   "queue overflow for kid" << workerId <<
                   " at " << queue->outSize(workerId) << " items");
            // TODO: grow queue size
        }
    }
}