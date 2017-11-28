static void
peerCheckAlwaysDirectDone(int answer, void *data)
{
    ps_state *psstate = (ps_state *)data;
    psstate->acl_checklist = NULL;
    debugs(44, 3, "peerCheckAlwaysDirectDone: " << answer);
    psstate->always_direct = answer ? 1 : -1;
    peerSelectFoo(psstate);
}