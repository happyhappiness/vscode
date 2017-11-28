int
icpUdpSend(int fd,
           const Ip::Address &to,
           icp_common_t * msg,
           const LogTags &logcode,
           int delay)
{
    icpUdpData *queue;
    int x;
    int len;
    len = (int) ntohs(msg->length);
    debugs(12, 5, "icpUdpSend: FD " << fd << " sending " <<
           icp_opcode_str[msg->opcode] << ", " << len << " bytes to " << to);

    x = comm_udp_sendto(fd, to, msg, len);

    if (x >= 0) {
        /* successfully written */
        icpLogIcp(to, logcode, len, (char *) (msg + 1), delay);
        icpCount(msg, SENT, (size_t) len, delay);
        safe_free(msg);
    } else if (0 == delay) {
        /* send failed, but queue it */
        queue = (icpUdpData *) xcalloc(1, sizeof(icpUdpData));
        queue->address = to;
        queue->msg = msg;
        queue->len = (int) ntohs(msg->length);
        queue->queue_time = current_time;
        queue->logcode = logcode;

        if (IcpQueueHead == NULL) {
            IcpQueueHead = queue;
            IcpQueueTail = queue;
        } else if (IcpQueueTail == IcpQueueHead) {
            IcpQueueTail = queue;
            IcpQueueHead->next = queue;
        } else {
            IcpQueueTail->next = queue;
            IcpQueueTail = queue;
        }

        Comm::SetSelect(fd, COMM_SELECT_WRITE, icpUdpSendQueue, NULL, 0);
        ++statCounter.icp.replies_queued;
    } else {
        /* don't queue it */
        ++statCounter.icp.replies_dropped;
    }

    return x;
}