void
lutil_sasl_freedefs(
    void *defaults)
{
    lutilSASLdefaults *defs = (lutilSASLdefaults *) defaults;

    xfree(defs->mech);
    xfree(defs->realm);
    xfree(defs->authcid);
    xfree(defs->passwd);
    xfree(defs->authzid);
    xfree(defs->resps);

    xfree(defs);
}