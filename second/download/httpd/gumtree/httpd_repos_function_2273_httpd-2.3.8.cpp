static int session_fixups(request_rec * r)
{
    session_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                  &session_module);

    session_rec *z = NULL;
    ap_session_load(r, &z);

    if (conf->env) {
        session_identity_encode(r, z);
        if (z->encoded) {
            apr_table_set(r->subprocess_env, HTTP_SESSION, z->encoded);
            z->encoded = NULL;
        }
    }

    return OK;

}