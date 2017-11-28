static void
authenticateStateFree(AuthenticateStateData * r)
{
    cbdataFree(r);
}