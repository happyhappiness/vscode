static void
peerGetSomeDirect(ps_state * ps)
{
    if (ps->direct == DIRECT_NO)
        return;

    /* WAIS is not implemented natively */
    if (ps->request->protocol == AnyP::PROTO_WAIS)
        return;

    peerAddFwdServer(&ps->servers, NULL, HIER_DIRECT);
}