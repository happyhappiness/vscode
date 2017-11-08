static int nwssl_hook_Fixup(request_rec *r)
{
    int i;

    if (!isSecure(r) && !isSecureUpgraded(r))
        return DECLINED;

    apr_table_set(r->subprocess_env, "HTTPS", "on");

    return DECLINED;
}