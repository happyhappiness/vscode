void
helperShutdown(helper * hlp)
{
    dlink_node *link = hlp->servers.head;
#ifdef _SQUID_MSWIN_

    HANDLE hIpc;
    pid_t pid;
    int no;
#endif

    while (link) {
        helper_server *srv;
        srv = (helper_server *)link->data;
        link = link->next;

        if (srv->flags.shutdown) {
            debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " has already SHUT DOWN.");
            continue;
        }

        hlp->n_active--;
        assert(hlp->n_active >= 0);
        srv->flags.shutdown = 1;	/* request it to shut itself down */

        if (srv->flags.closing) {
            debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is CLOSING.");
            continue;
        }

        if (srv->stats.pending) {
            debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is BUSY.");
            continue;
        }

        srv->flags.closing = 1;
#ifdef _SQUID_MSWIN_

        hIpc = srv->hIpc;
        pid = srv->pid;
        no = srv->index + 1;
        shutdown(srv->wfd, SD_BOTH);
#endif

        debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " shutting down.");
        /* the rest of the details is dealt with in the helperServerFree
         * close handler
         */
        comm_close(srv->rfd);
#ifdef _SQUID_MSWIN_

        if (hIpc) {
            if (WaitForSingleObject(hIpc, 5000) != WAIT_OBJECT_0) {
                getCurrentTime();
                debugs(84, 1, "helperShutdown: WARNING: " << hlp->id_name <<
                       " #" << no << " (" << hlp->cmdline->key << "," <<
                       (long int)pid << ") didn't exit in 5 seconds");

            }

            CloseHandle(hIpc);
        }

#endif

    }
}