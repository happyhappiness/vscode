void
commHandleWriteHelper(void * data)
{
    CommQuotaQueue *queue = static_cast<CommQuotaQueue*>(data);
    assert(queue);

    ClientInfo *clientInfo = queue->clientInfo;
    // ClientInfo invalidates queue if freed, so if we got here through,
    // evenAdd cbdata protections, everything should be valid and consistent
    assert(clientInfo);
    assert(clientInfo->hasQueue());
    assert(clientInfo->hasQueue(queue));
    assert(!clientInfo->selectWaiting);
    assert(clientInfo->eventWaiting);
    clientInfo->eventWaiting = false;

    do {
        // check that the head descriptor is still relevant
        const int head = clientInfo->quotaPeekFd();
        Comm::IoCallback *ccb = COMMIO_FD_WRITECB(head);

        if (fd_table[head].clientInfo == clientInfo &&
                clientInfo->quotaPeekReserv() == ccb->quotaQueueReserv &&
                !fd_table[head].closing()) {

            // wait for the head descriptor to become ready for writing
            Comm::SetSelect(head, COMM_SELECT_WRITE, Comm::HandleWrite, ccb, 0);
            clientInfo->selectWaiting = true;
            return;
        }

        clientInfo->quotaDequeue(); // remove the no longer relevant descriptor
        // and continue looking for a relevant one
    } while (clientInfo->hasQueue());

    debugs(77,3, HERE << "emptied queue");
}