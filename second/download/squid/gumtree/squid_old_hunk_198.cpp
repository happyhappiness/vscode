        // quit reading if there is no space left
        if (!spaceSize) {
            debugs(84, DBG_IMPORTANT, "ERROR: Disconnecting from a " <<
                   "helper that overflowed " << srv->rbuf_sz << "-byte " <<
                   "Squid input buffer: " << hlp->id_name << " #" <<
                   (srv->index + 1));
            int wfd = srv->wfd;
            srv->wfd = -1;
            if (srv->rfd == wfd)
                srv->rfd = -1;
            srv->flags.closing=1;
            comm_close(wfd);

#if _SQUID_MSWIN_
            if (srv->hIpc) {
                if (WaitForSingleObject(srv->hIpc, 5000) != WAIT_OBJECT_0) {
                    getCurrentTime();
                    debugs(84, 1, "helperShutdown: WARNING: " << hlp->id_name <<
                           " #" << no << " (" << hlp->cmdline->key << "," <<
                           (long int)srv->pid << ") didn't exit in 5 seconds");
                }
                CloseHandle(srv->hIpc);
            }
#endif
            return;
        }

        comm_read(srv->rfd, srv->rbuf + srv->roffset, spaceSize, helperStatefulHandleRead, srv);
    }
}

static void
Enqueue(helper * hlp, helper_request * r)
{
    dlink_node *link = (dlink_node *)memAllocate(MEM_DLINK_NODE);
    dlinkAddTail(r, link, &hlp->queue);
    hlp->stats.queue_size++;

    if (hlp->stats.queue_size < hlp->n_running)
        return;

    if (squid_curtime - hlp->last_queue_warn < 600)
        return;

    if (shutting_down || reconfiguring)
        return;

    hlp->last_queue_warn = squid_curtime;

    debugs(84, 0, "WARNING: All " << hlp->id_name << " processes are busy.");
    debugs(84, 0, "WARNING: " << hlp->stats.queue_size << " pending requests queued");


    if (hlp->stats.queue_size > hlp->n_running * 2)
        fatalf("Too many queued %s requests", hlp->id_name);

    debugs(84, 1, "Consider increasing the number of " << hlp->id_name << " processes in your config file.");

}

static void
StatefulEnqueue(statefulhelper * hlp, helper_stateful_request * r)
{
    dlink_node *link = (dlink_node *)memAllocate(MEM_DLINK_NODE);
    dlinkAddTail(r, link, &hlp->queue);
    hlp->stats.queue_size++;

    if (hlp->stats.queue_size < hlp->n_running)
        return;

    if (hlp->stats.queue_size > hlp->n_running * 2)
        fatalf("Too many queued %s requests", hlp->id_name);

    if (squid_curtime - hlp->last_queue_warn < 600)
        return;

    if (shutting_down || reconfiguring)
        return;

    hlp->last_queue_warn = squid_curtime;

    debugs(84, 0, "WARNING: All " << hlp->id_name << " processes are busy.");

    debugs(84, 0, "WARNING: " << hlp->stats.queue_size << " pending requests queued");
    debugs(84, 1, "Consider increasing the number of " << hlp->id_name << " processes in your config file.");

}

static helper_request *
Dequeue(helper * hlp)
{
    dlink_node *link;
    helper_request *r = NULL;

    if ((link = hlp->queue.head)) {
        r = (helper_request *)link->data;
        dlinkDelete(link, &hlp->queue);
        memFree(link, MEM_DLINK_NODE);
        hlp->stats.queue_size--;
    }

    return r;
}

static helper_stateful_request *
