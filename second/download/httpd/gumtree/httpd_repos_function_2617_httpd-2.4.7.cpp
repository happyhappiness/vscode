static int nwssl_hook_Fixup(request_rec *r)
{
    if (!isSecure(r) && !isSecureUpgraded(r))
        return DECLINED;

    apr_table_setn(r->subprocess_env, "HTTPS", "on");

    return DECLINED;
}