void
lutil_sasl_freedefs(
    void *defaults)
{
    lutilSASLdefaults *defs = (lutilSASLdefaults *) defaults;

    if (defs->mech)
        xfree(defs->mech);
    if (defs->realm)
        xfree(defs->realm);
    if (defs->authcid)
        xfree(defs->authcid);
    if (defs->passwd)
        xfree(defs->passwd);
    if (defs->authzid)
        xfree(defs->authzid);
    if (defs->resps)
        xfree(defs->resps);

    xfree(defs);
}