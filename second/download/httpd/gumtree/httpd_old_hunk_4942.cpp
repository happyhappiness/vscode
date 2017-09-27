        return return_code;
    }

    return OK;
}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_check_authn(authenticate_basic_user, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_note_auth_failure(hook_note_basic_auth_failure, NULL, NULL,
                              APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(auth_basic) =
{
    STANDARD20_MODULE_STUFF,
    create_auth_basic_dir_config,  /* dir config creater */
    NULL,                          /* dir merger --- default is to override */
    NULL,                          /* server config */
    NULL,                          /* merge server config */
    auth_basic_cmds,               /* command apr_table_t */
    register_hooks                 /* register hooks */
};
