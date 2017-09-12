int clusterAddSlot(clusterNode *n, int slot) {
    redisAssert(clusterNodeSetSlotBit(n,slot) == 0);
    server.cluster.slots[slot] = n;
    return REDIS_OK;
}

