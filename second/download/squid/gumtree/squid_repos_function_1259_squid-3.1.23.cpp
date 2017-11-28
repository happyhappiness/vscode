static void
peerSelectFoo(ps_state * ps)
{
    StoreEntry *entry = ps->entry;
    HttpRequest *request = ps->request;
    debugs(44, 3, "peerSelectFoo: '" << RequestMethodStr(request->method) << " " << request->GetHost() << "'");

    /** If we don't known whether DIRECT is permitted ... */
    if (ps->direct == DIRECT_UNKNOWN) {
        if (ps->always_direct == 0 && Config.accessList.AlwaysDirect) {
            /** check always_direct; */
            ps->acl_checklist = new ACLFilledChecklist(
                Config.accessList.AlwaysDirect,
                request,
                NULL);		/* ident */
            ps->acl_checklist->nonBlockingCheck(peerCheckAlwaysDirectDone, ps);
            return;
        } else if (ps->always_direct > 0) {
            /** if always_direct says YES, do that. */
            ps->direct = DIRECT_YES;
        } else if (ps->never_direct == 0 && Config.accessList.NeverDirect) {
            /** check never_direct; */
            ps->acl_checklist = new ACLFilledChecklist(
                Config.accessList.NeverDirect,
                request,
                NULL);		/* ident */
            ps->acl_checklist->nonBlockingCheck(peerCheckNeverDirectDone,
                                                ps);
            return;
        } else if (ps->never_direct > 0) {
            /** if always_direct says NO, do that. */
            ps->direct = DIRECT_NO;
        } else if (request->flags.no_direct) {
            /** if we are accelerating, direct is not an option. */
            ps->direct = DIRECT_NO;
        } else if (request->flags.loopdetect) {
            /** if we are in a forwarding-loop, direct is not an option. */
            ps->direct = DIRECT_YES;
        } else if (peerCheckNetdbDirect(ps)) {
            ps->direct = DIRECT_YES;
        } else {
            ps->direct = DIRECT_MAYBE;
        }

        debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct]);
    }

    if (!entry || entry->ping_status == PING_NONE)
        peerSelectPinned(ps);
    if (entry == NULL) {
        (void) 0;
    } else if (entry->ping_status == PING_NONE) {
        peerGetSomeNeighbor(ps);

        if (entry->ping_status == PING_WAITING)
            return;
    } else if (entry->ping_status == PING_WAITING) {
        peerGetSomeNeighborReplies(ps);
        entry->ping_status = PING_DONE;
    }

    switch (ps->direct) {

    case DIRECT_YES:
        peerGetSomeDirect(ps);
        break;

    case DIRECT_NO:
        peerGetSomeParent(ps);
        peerGetAllParents(ps);
        break;

    default:

        if (Config.onoff.prefer_direct)
            peerGetSomeDirect(ps);

        if (request->flags.hierarchical || !Config.onoff.nonhierarchical_direct)
            peerGetSomeParent(ps);

        if (!Config.onoff.prefer_direct)
            peerGetSomeDirect(ps);

        break;
    }

    peerSelectCallback(ps);
}