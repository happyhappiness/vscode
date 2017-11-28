void
helperStatefulShutdown(statefulhelper * hlp)
{
    dlink_node *link = hlp->servers.head;
    helper_stateful_server *srv;

    while (link) {
        srv = (helper_stateful_server *)link->data;
        link = link->next;

        if (srv->flags.shutdown) {
            debugs(84, 3, "helperStatefulShutdown: " << hlp->id_name << " #" << srv->index + 1 << " has already SHUT DOWN.");
            continue;
        }

        assert(hlp->childs.n_active > 0);
        -- hlp->childs.n_active;
        srv->flags.shutdown = 1;	/* request it to shut itself down */

        if (srv->flags.busy) {
            debugs(84, 3, "helperStatefulShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is BUSY.");
            continue;
        }

        if (srv->flags.closing) {
            debugs(84, 3, "helperStatefulShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is CLOSING.");
            continue;
        }

        if (srv->flags.reserved) {
            if (shutting_down) {
                debugs(84, 3, "helperStatefulShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is RESERVED. Closing anyway.");
            } else {
                debugs(84, 3, "helperStatefulShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is RESERVED. Not Shutting Down Yet.");
                continue;
            }
        }

        debugs(84, 3, "helperStatefulShutdown: " << hlp->id_name << " #" << srv->index + 1 << " shutting down.");

        /* the rest of the details is dealt with in the helperStatefulServerFree
         * close handler
         */
        srv->closePipesSafely();
    }
}