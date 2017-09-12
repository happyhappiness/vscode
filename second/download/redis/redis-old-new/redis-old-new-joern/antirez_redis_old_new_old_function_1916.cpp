void clusterBeforeSleep(void) {
    if (server.cluster->handle_slave_failover_asap) {
        clusterHandleSlaveFailover();
        server.cluster->handle_slave_failover_asap = 0;
    }
}