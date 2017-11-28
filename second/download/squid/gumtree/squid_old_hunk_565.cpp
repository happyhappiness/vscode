    storeAppendPrintf(sentry, "queue length: %d\n",
                      hlp->stats.queue_size);
    storeAppendPrintf(sentry, "avg service time: %d msec\n",
                      hlp->stats.avg_svc_time);
    storeAppendPrintf(sentry, "\n");
    storeAppendPrintf(sentry, "%7s\t%7s\t%7s\t%11s\t%11s\t%6s\t%7s\t%7s\t%7s\n",
                      "#",
                      "FD",
                      "PID",
                      "# Requests",
                      "# Replies",
                      "Flags",
                      "Time",
                      "Offset",
                      "Request");

    for (dlink_node *link = hlp->servers.head; link; link = link->next) {
        helper_stateful_server *srv = (helper_stateful_server *)link->data;
        double tt = 0.001 * tvSubMsec(srv->dispatch_time, srv->flags.busy ? current_time : srv->answer_time);
        storeAppendPrintf(sentry, "%7d\t%7d\t%7d\t%11" PRIu64 "\t%11" PRIu64 "\t%c%c%c%c%c\t%7.3f\t%7d\t%s\n",
                          srv->index + 1,
                          srv->readPipe->fd,
                          srv->pid,
                          srv->stats.uses,
                          srv->stats.replies,
                          srv->flags.busy ? 'B' : ' ',
                          srv->flags.closing ? 'C' : ' ',
