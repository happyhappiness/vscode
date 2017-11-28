static void
peerSelectFoo(ps_state * ps)
{
    if (!cbdataReferenceValid(ps->callback_data)) {
        debugs(44, 3, "Aborting peer selection. Parent Job went away.");
        delete ps;
        return;
    }

    StoreEntry *entry = ps->entry;
    HttpRequest *request = ps->request;
    debugs(44, 3, request->method << ' ' << request->GetHost());

    /** If we don't know whether DIRECT is permitted ... */
    if (ps->direct == DIRECT_UNKNOWN) {
        if (ps->always_direct == ACCESS_DUNNO) {
            debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct] << " (always_direct to be checked)");
            /** check always_direct; */
            ACLFilledChecklist *ch = new ACLFilledChecklist(Config.accessList.AlwaysDirect, request, NULL);
            ch->al = ps->al;
            ps->acl_checklist = ch;
            ps->acl_checklist->nonBlockingCheck(peerCheckAlwaysDirectDone, ps);
            return;
        } else if (ps->never_direct == ACCESS_DUNNO) {
            debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct] << " (never_direct to be checked)");
            /** check never_direct; */
            ACLFilledChecklist *ch = new ACLFilledChecklist(Config.accessList.NeverDirect, request, NULL);
            ch->al = ps->al;
            ps->acl_checklist = ch;
            ps->acl_checklist->nonBlockingCheck(peerCheckNeverDirectDone, ps);
            return;
        } else if (request->flags.noDirect) {
            /** if we are accelerating, direct is not an option. */
            ps->direct = DIRECT_NO;
            debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct] << " (forced non-direct)");
        } else if (request->flags.loopDetected) {
            /** if we are in a forwarding-loop, direct is not an option. */
            ps->direct = DIRECT_YES;
            debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct] << " (forwarding loop detected)");
        } else if (peerCheckNetdbDirect(ps)) {
            ps->direct = DIRECT_YES;
            debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct] << " (checkNetdbDirect)");
        } else {
            ps->direct = DIRECT_MAYBE;
            debugs(44, 3, "peerSelectFoo: direct = " << DirectStr[ps->direct] << " (default)");
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

        if (request->flags.hierarchical || !Config.onoff.nonhierarchical_direct) {
            peerGetSomeParent(ps);
            peerGetAllParents(ps);
        }

        if (!Config.onoff.prefer_direct)
            peerGetSomeDirect(ps);

        break;
    }

    // resolve the possible peers
    peerSelectDnsPaths(ps);
}