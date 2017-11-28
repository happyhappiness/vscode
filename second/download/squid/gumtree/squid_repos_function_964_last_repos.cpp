void
PeerPoolMgrsRr::syncConfig()
{
    for (CachePeer *p = Config.peers; p; p = p->next) {
        // On reconfigure, Squid deletes the old config (and old peers in it),
        // so should always be dealing with a brand new configuration.
        assert(!p->standby.mgr);
        assert(!p->standby.pool);
        if (p->standby.limit) {
            p->standby.mgr = new PeerPoolMgr(p);
            p->standby.pool = new PconnPool(p->name, p->standby.mgr);
            AsyncJob::Start(p->standby.mgr.get());
        }
    }
}