static int
AddToMap(const PendingOpenRequest &por)
{
    // find unused ID using linear seach; there should not be many entries
    for (int id = 0; true; ++id) {
        if (TheSharedListenRequestMap.find(id) == TheSharedListenRequestMap.end()) {
            TheSharedListenRequestMap[id] = por;
            return id;
        }
    }
    assert(false); // not reached
    return -1;
}