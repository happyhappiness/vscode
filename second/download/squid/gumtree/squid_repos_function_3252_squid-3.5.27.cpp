void
CollapsedForwarding::HandleNewData(const char *const when)
{
    debugs(17, 4, "popping all " << when);
    CollapsedForwardingMsg msg;
    int workerId;
    int poppedCount = 0;
    while (queue->pop(workerId, msg)) {
        debugs(17, 3, "message from kid" << workerId);
        if (workerId != msg.sender) {
            debugs(17, DBG_IMPORTANT, "mismatching kid IDs: " << workerId <<
                   " != " << msg.sender);
        }

        debugs(17, 7, "handling entry " << msg.xitIndex << " in transients_map");
        Store::Root().syncCollapsed(msg.xitIndex);
        debugs(17, 7, "handled entry " << msg.xitIndex << " in transients_map");

        // XXX: stop and schedule an async call to continue
        ++poppedCount;
        assert(poppedCount < SQUID_MAXFD);
    }
}