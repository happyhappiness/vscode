    }
}

void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
