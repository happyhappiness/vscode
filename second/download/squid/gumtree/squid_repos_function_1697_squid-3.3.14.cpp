void
helperShutdown(helper * hlp)
{
    dlink_node *link = hlp->servers.head;

    while (link) {
        helper_server *srv;
        srv = (helper_server *)link->data;
        link = link->next;

        if (srv->flags.shutdown) {
            debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " has already SHUT DOWN.");
            continue;
        }

        assert(hlp->childs.n_active > 0);
        -- hlp->childs.n_active;
        srv->flags.shutdown = 1;	/* request it to shut itself down */

        if (srv->flags.closing) {
            debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is CLOSING.");
            continue;
        }

        if (srv->stats.pending) {
            debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " is BUSY.");
            continue;
        }

        debugs(84, 3, "helperShutdown: " << hlp->id_name << " #" << srv->index + 1 << " shutting down.");
        /* the rest of the details is dealt with in the helperServerFree
         * close handler
         */
        srv->closePipesSafely();
    }
}