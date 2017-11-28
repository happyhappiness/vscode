static void
peerSelectStateFree(ps_state * psstate)
{
    if (psstate->acl_checklist) {
        debugs(44, 1, "calling aclChecklistFree() from peerSelectStateFree");
        delete (psstate->acl_checklist);
    }

    HTTPMSGUNLOCK(psstate->request);

    if (psstate->entry) {
        assert(psstate->entry->ping_status != PING_WAITING);
        psstate->entry->unlock();
        psstate->entry = NULL;
    }

    cbdataFree(psstate);
}