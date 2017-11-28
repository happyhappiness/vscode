static void
icpCount(void *buf, int which, size_t len, int delay)
{
    icp_common_t *icp = (icp_common_t *) buf;

    if (len < sizeof(*icp))
        return;

    if (SENT == which) {
        statCounter.icp.pkts_sent++;
        kb_incr(&statCounter.icp.kbytes_sent, len);

        if (ICP_QUERY == icp->opcode) {
            statCounter.icp.queries_sent++;
            kb_incr(&statCounter.icp.q_kbytes_sent, len);
        } else {
            statCounter.icp.replies_sent++;
            kb_incr(&statCounter.icp.r_kbytes_sent, len);
            /* this is the sent-reply service time */
            statHistCount(&statCounter.icp.reply_svc_time, delay);
        }

        if (ICP_HIT == icp->opcode)
            statCounter.icp.hits_sent++;
    } else if (RECV == which) {
        statCounter.icp.pkts_recv++;
        kb_incr(&statCounter.icp.kbytes_recv, len);

        if (ICP_QUERY == icp->opcode) {
            statCounter.icp.queries_recv++;
            kb_incr(&statCounter.icp.q_kbytes_recv, len);
        } else {
            statCounter.icp.replies_recv++;
            kb_incr(&statCounter.icp.r_kbytes_recv, len);
            /* statCounter.icp.query_svc_time set in clientUpdateCounters */
        }

        if (ICP_HIT == icp->opcode)
            statCounter.icp.hits_recv++;
    }
}