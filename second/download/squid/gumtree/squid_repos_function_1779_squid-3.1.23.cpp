static void
neighborRemove(peer * target)
{
    peer *p = NULL;
    peer **P = NULL;
    p = Config.peers;
    P = &Config.peers;

    while (p) {
        if (target == p)
            break;

        P = &p->next;

        p = p->next;
    }

    if (p) {
        *P = p->next;
        cbdataFree(p);
        Config.npeers--;
    }

    first_ping = Config.peers;
}