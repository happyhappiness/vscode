void
icpUdpSendQueue(int fd, void *unused)
{
    icpUdpData *q;
    int x;
    int delay;

    while ((q = IcpQueueHead) != NULL) {
        delay = tvSubUsec(q->queue_time, current_time);
        /* increment delay to prevent looping */
        x = icpUdpSend(fd, q->address, (icp_common_t *) q->msg, q->logcode, ++delay);
        IcpQueueHead = q->next;
        safe_free(q);

        if (x < 0)
            break;
    }
}