void
Comm::IoCallback::selectOrQueueWrite()
{
#if USE_DELAY_POOLS
    // stand in line if there is one
    if (ClientInfo *clientInfo = fd_table[conn->fd].clientInfo) {
        if (clientInfo->writeLimitingActive) {
            quotaQueueReserv = clientInfo->quotaEnqueue(conn->fd);
            clientInfo->kickQuotaQueue();
            return;
        }
    }
#endif

    SetSelect(conn->fd, COMM_SELECT_WRITE, Comm::HandleWrite, this, 0);
}