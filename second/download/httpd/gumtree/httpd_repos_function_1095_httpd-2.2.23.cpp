static void register_hooks(apr_pool_t *p)
{
    static const char * const aszSucc[]={ "mod_userdir.c",
                                          "mod_vhost_alias.c",NULL };

    ap_hook_translate_name(translate_alias_redir,NULL,aszSucc,APR_HOOK_MIDDLE);
    ap_hook_fixups(fixup_redir,NULL,NULL,APR_HOOK_MIDDLE);
}