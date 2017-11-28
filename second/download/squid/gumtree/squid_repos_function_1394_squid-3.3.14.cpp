void
icpUdpSendQueue(int fd, void *unused)
{
    icpUdpData *q;

    while ((q = IcpQueueHead) != NULL) {
        int delay = tvSubUsec(q->queue_time, current_time);
        /* increment delay to prevent looping */
        const int x = icpUdpSend(fd, q->address, (icp_common_t *) q->msg, q->logcode, ++delay);
        IcpQueueHead = q->next;
        xfree(q);

        if (x < 0)
            break;
    }
}