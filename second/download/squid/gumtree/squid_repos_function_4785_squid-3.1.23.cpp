void
authenticateAuthUserMerge(AuthUser * from, AuthUser * to)
{
    to->absorb (from);
}