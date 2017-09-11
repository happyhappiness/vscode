/* This function is called before the event handler returns to sleep for
 * events. It is useful to perform operations that must be done ASAP in
 * reaction to events fired but that are not safe to perform inside event
 * handlers. */
void clusterBeforeSleep(void) {
    if (server.cluster->handle_slave_failover_asap) {
        clusterHandleSlaveFailover();
        server.cluster->handle_slave_failover_asap = 0;
    }
}

/* -----------------------------------------------------------------------------
