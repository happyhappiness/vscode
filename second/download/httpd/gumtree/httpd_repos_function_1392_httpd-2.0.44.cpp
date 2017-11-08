static int nwssl_hook_Fixup(request_rec *r)
{
    apr_table_t *e = r->subprocess_env;    
    if (!isSecure(r))
        return DECLINED;

    apr_table_set(e, "HTTPS", "on");
    
    return DECLINED;
}