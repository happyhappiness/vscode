static void
peerCheckAlwaysDirectDone(allow_t answer, void *data)
{
    ps_state *psstate = (ps_state *)data;
    psstate->acl_checklist = NULL;
    debugs(44, 3, "peerCheckAlwaysDirectDone: " << answer);
    psstate->always_direct = answer;
    switch (answer) {
    case ACCESS_ALLOWED:
        /** if always_direct says YES, do that. */
        psstate->direct = DIRECT_YES;
        debugs(44, 3, HERE << "direct = " << DirectStr[psstate->direct] << " (always_direct allow)");
        break;
    case ACCESS_DENIED: // not relevant.
    case ACCESS_DUNNO:  // not relevant.
        break;
    case ACCESS_AUTH_REQUIRED:
        debugs(44, DBG_IMPORTANT, "WARNING: always_direct resulted in " << answer << ". Username ACLs are not reliable here.");
        break;
    }
    peerSelectFoo(psstate);
}