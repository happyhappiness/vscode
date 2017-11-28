void
Adaptation::AccessRule::finalize()
{
    if (!group()) { // no explicit group
        debugs(93,7, HERE << "no service group: " << groupId);
        // try to add a one-service group
        if (FindService(groupId) != NULL) {
            ServiceGroupPointer g = new SingleService(groupId);
            g->finalize(); // explicit groups were finalized before rules
            AllGroups().push_back(g);
        }
    }

    if (!group()) {
        debugs(93, DBG_CRITICAL, "ERROR: Unknown adaptation service or group name: '" <<
               groupId << "'"); // TODO: fail on failures
    }
}