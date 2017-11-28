static void
peerSelectStateFree(ps_state * psstate)
{
    if (psstate->entry) {
        debugs(44, 3, HERE << psstate->entry->url());

        if (psstate->entry->ping_status == PING_WAITING)
            eventDelete(peerPingTimeout, psstate);

        psstate->entry->ping_status = PING_DONE;
    }

    if (psstate->acl_checklist) {
        debugs(44, DBG_IMPORTANT, "calling aclChecklistFree() from peerSelectStateFree");
        delete (psstate->acl_checklist);
    }

    HTTPMSGUNLOCK(psstate->request);

    if (psstate->entry) {
        assert(psstate->entry->ping_status != PING_WAITING);
        psstate->entry->unlock();
        psstate->entry = NULL;
    }

    delete psstate->lastError;

    cbdataFree(psstate);
}