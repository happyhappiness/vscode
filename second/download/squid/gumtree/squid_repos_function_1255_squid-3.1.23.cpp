static void
peerCheckNeverDirectDone(int answer, void *data)
{
    ps_state *psstate = (ps_state *) data;
    psstate->acl_checklist = NULL;
    debugs(44, 3, "peerCheckNeverDirectDone: " << answer);
    psstate->never_direct = answer ? 1 : -1;
    peerSelectFoo(psstate);
}