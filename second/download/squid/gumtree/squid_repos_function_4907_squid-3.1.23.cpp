static void
authenticateStateFree(authenticateStateData * r)
{
    AUTHUSERREQUESTUNLOCK(r->auth_user_request, "r");
    cbdataFree(r);
}