static void
peerCheckNeverDirectDone(allow_t answer, void *data)
{
    ps_state *psstate = (ps_state *) data;
    psstate->acl_checklist = NULL;
    debugs(44, 3, "peerCheckNeverDirectDone: " << answer);
    psstate->never_direct = answer;
    switch (answer) {
    case ACCESS_ALLOWED:
        /** if never_direct says YES, do that. */
        psstate->direct = DIRECT_NO;
        debugs(44, 3, HERE << "direct = " << DirectStr[psstate->direct] << " (never_direct allow)");
        break;
    case ACCESS_DENIED: // not relevant.
    case ACCESS_DUNNO:  // not relevant.
        break;
    case ACCESS_AUTH_REQUIRED:
        debugs(44, DBG_IMPORTANT, "WARNING: never_direct resulted in " << answer << ". Username ACLs are not reliable here.");
        break;
    }
    peerSelectFoo(psstate);
}