        *P = p->next;
#if USE_CACHE_DIGESTS

        cbdataReferenceDone(p->digest);
#endif

        // the mgr job will notice that its owner is gone and stop
        PeerPoolMgr::Checkpoint(p->standby.mgr, "peer gone");
        delete p->standby.pool;
        cbdataFree(p);
    }

    Config.npeers = 0;
}

