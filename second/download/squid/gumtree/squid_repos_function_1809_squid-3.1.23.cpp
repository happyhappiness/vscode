static void
peerCountMcastPeersDone(void *data)
{
    ps_state *psstate = (ps_state *)data;
    StoreEntry *fake = psstate->entry;

    if (cbdataReferenceValid(psstate->callback_data)) {
        peer *p = (peer *)psstate->callback_data;
        p->mcast.flags.counting = 0;
        p->mcast.avg_n_members = Math::doubleAverage(p->mcast.avg_n_members, (double) psstate->ping.n_recv, ++p->mcast.n_times_counted, 10);
        debugs(15, 1, "Group " << p->host  << ": " << psstate->ping.n_recv  <<
               " replies, "<< std::setw(4)<< std::setprecision(2) <<
               p->mcast.avg_n_members <<" average, RTT " << p->stats.rtt);
        p->mcast.n_replies_expected = (int) p->mcast.avg_n_members;
    }

    cbdataReferenceDone(psstate->callback_data);

    EBIT_SET(fake->flags, ENTRY_ABORTED);
    HTTPMSGUNLOCK(fake->mem_obj->request);
    fake->releaseRequest();
    fake->unlock();
    HTTPMSGUNLOCK(psstate->request);
    cbdataFree(psstate);
}