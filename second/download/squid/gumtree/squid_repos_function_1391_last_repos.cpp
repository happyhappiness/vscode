void
helper::packStatsInto(Packable *p, const char *label) const
{
    if (label)
        p->appendf("%s:\n", label);

    p->appendf("  program: %s\n", cmdline->key);
    p->appendf("  number active: %d of %d (%d shutting down)\n", childs.n_active, childs.n_max, (childs.n_running - childs.n_active));
    p->appendf("  requests sent: %d\n", stats.requests);
    p->appendf("  replies received: %d\n", stats.replies);
    p->appendf("  requests timedout: %d\n", stats.timedout);
    p->appendf("  queue length: %d\n", stats.queue_size);
    p->appendf("  avg service time: %d msec\n", stats.avg_svc_time);
    p->append("\n",1);
    p->appendf("%7s\t%7s\t%7s\t%11s\t%11s\t%11s\t%6s\t%7s\t%7s\t%7s\n",
               "ID #",
               "FD",
               "PID",
               "# Requests",
               "# Replies",
               "# Timed-out",
               "Flags",
               "Time",
               "Offset",
               "Request");

    for (dlink_node *link = servers.head; link; link = link->next) {
        HelperServerBase *srv = static_cast<HelperServerBase *>(link->data);
        assert(srv);
        Helper::Xaction *xaction = srv->requests.empty() ? NULL : srv->requests.front();
        double tt = 0.001 * (xaction ? tvSubMsec(xaction->request.dispatch_time, current_time) : tvSubMsec(srv->dispatch_time, srv->answer_time));
        p->appendf("%7u\t%7d\t%7d\t%11" PRIu64 "\t%11" PRIu64 "\t%11" PRIu64 "\t%c%c%c%c%c%c\t%7.3f\t%7d\t%s\n",
                   srv->index.value,
                   srv->readPipe->fd,
                   srv->pid,
                   srv->stats.uses,
                   srv->stats.replies,
                   srv->stats.timedout,
                   srv->stats.pending ? 'B' : ' ',
                   srv->flags.writing ? 'W' : ' ',
                   srv->flags.closing ? 'C' : ' ',
                   srv->flags.reserved ? 'R' : ' ',
                   srv->flags.shutdown ? 'S' : ' ',
                   xaction && xaction->request.placeholder ? 'P' : ' ',
                   tt < 0.0 ? 0.0 : tt,
                   (int) srv->roffset,
                   xaction ? Format::QuoteMimeBlob(xaction->request.buf) : "(none)");
    }

    p->append("\nFlags key:\n"
              "   B\tBUSY\n"
              "   W\tWRITING\n"
              "   C\tCLOSING\n"
              "   R\tRESERVED\n"
              "   S\tSHUTDOWN PENDING\n"
              "   P\tPLACEHOLDER\n", 101);
}