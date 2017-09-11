     * 2) We are a slave and our master is left without slots. We need
     *    to replicate to the new slots owner. */
    if (newmaster && curmaster->numslots == 0) {
        redisLog(REDIS_WARNING,
            "Configuration change detected. Reconfiguring myself "
            "as a replica of %.40s", sender->name);
        clusterSetMaster(sender);
